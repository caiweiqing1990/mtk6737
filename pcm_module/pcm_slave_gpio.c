#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/types.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/io.h>
#include "gpio_cfg.h"

#define TAG                "[PCM_SLAVE] "
#define GPIOLOG(fmt, arg...)   pr_debug(TAG fmt, ##arg)
#define GPIOMSG(fmt, arg...)   pr_warn(fmt, ##arg)
#define GPIOERR(fmt, arg...)   pr_err(TAG "======================%5d: "fmt, __LINE__, ##arg)

#define DATA_LOW			0
#define DATA_HIGH			1
#define DIR_IN				0
#define DIR_OUT				1

#define PCM_IOC_MAGIC 		0x81
#define PCM_START           _IO(PCM_IOC_MAGIC, 0x01)
#define PCM_READ_PCM        _IOR(PCM_IOC_MAGIC, 0x02, uint32_t)
#define PCM_WRITE_PCM       _IOW(PCM_IOC_MAGIC, 0x03, uint32_t)
#define PCM_STOP          	_IO(PCM_IOC_MAGIC, 0x04)

#define	PCM1_CLK			61
#define	PCM1_SYNC			62
#define	PCM1_DI				63
#define	PCM1_DO0			64

#define PCM_BITS			16
#define PCM_RATE			8000
#define PCM_CHANNAL			1

#define GPIO_MODE_00		0

static void __iomem *gpio_regs = NULL;
static struct task_struct *pcm_kthread = NULL;

#define FRAME_SIZE	2 //unsigned short

#define PLAYBACK_PERIOD_SIZE	1600
#define PLAYBACK_BUF_SIZE 		(8*PLAYBACK_PERIOD_SIZE)
static unsigned short *playbackbuf = NULL;
static int playbackr=0;			//playback	∂¡Œª÷√
static int playbackw=0;			//playback	–¥Œª÷√
static int isplaybackStart=0;

#define RECORD_PERIOD_SIZE		1600
#define RECORD_BUF_SIZE 		(8*RECORD_PERIOD_SIZE)
static unsigned short *recordbuf = NULL;

static int recordr=0;			//record	∂¡Œª÷√
static int recordw=0;			//record	–¥Œª÷√
static int isrecordStart=0;

static DECLARE_WAIT_QUEUE_HEAD(waitq_r);
static volatile int ev_r = 1;	//record

static DECLARE_WAIT_QUEUE_HEAD(waitq_t);
static volatile int ev_t = 1;	//playback

static int is_playbackbuf_full(void)
{
	return ((playbackw + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE == playbackr);
}

static int is_playbackbuf_empty(void)
{
	return (playbackr == playbackw);
}

static void setplayback(void)
{
	playbackr = playbackw = isplaybackStart = 0;
	ev_t = 1;
}

static int is_recordbuf_full(void)
{
	return ((recordw + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE == recordr);
}

static int is_recordbuf_empty(void)
{
	return (recordr == recordw);
}

static void setrecord(void)
{
	recordr = recordw = isrecordStart = 0;
	ev_r = 1;
}

extern int mt_set_gpio_mode(unsigned long pin, unsigned long mode);

static int get_gpio_in_val(unsigned long pin)
{
	unsigned long bit;
	unsigned long reg;

	bit = DIN_offset[pin].offset;
	reg = *(volatile unsigned int *)(gpio_regs + DIN_addr[pin].addr);
	return ((reg & (1L << bit)) != 0) ? 1 : 0;
}

static void gpio_set_out(unsigned long pin, unsigned long output)
{
	if(output == 0)
	{
		//mt_reg_sync_writel(1L << DATAOUT_offset[pin].offset, (gpio_regs + DATAOUT_addr[pin].addr + 8));
		*(volatile unsigned int *)(gpio_regs + DATAOUT_addr[pin].addr + 8) = 1L << DATAOUT_offset[pin].offset;
	}
	else
	{
		//mt_reg_sync_writel(1L << DATAOUT_offset[pin].offset, (gpio_regs + DATAOUT_addr[pin].addr + 4));
		*(volatile unsigned int *)(gpio_regs + DATAOUT_addr[pin].addr + 4) = 1L << DATAOUT_offset[pin].offset;
	}
}

static void gpio_set_dir(unsigned long pin, unsigned long dir)
{
	if(dir == 0)
	{
		//mt_reg_sync_writel(1L << DIR_offset[pin].offset, (gpio_regs + DIR_addr[pin].addr + 8));
		*(volatile unsigned int *)(gpio_regs + DIR_addr[pin].addr + 8) = 1L << DIR_offset[pin].offset;
	}
	else
	{
		//mt_reg_sync_writel(1L << DIR_offset[pin].offset, (gpio_regs + DIR_addr[pin].addr + 4));
		*(volatile unsigned int *)(gpio_regs + DIR_addr[pin].addr + 4) = 1L << DIR_offset[pin].offset;
	}
}

#if 0
static unsigned short handle_pcm_frame(unsigned short val_do, int enable_data_out, int enable_data_in)
{
	int i;
	unsigned short val_di=0;
	
	gpio_set_out(PCM1_SYNC, DATA_HIGH);
	udelay(6);
	gpio_set_out(PCM1_SYNC, DATA_LOW);
	
	for(i=0; i<PCM_BITS; i++)
	{
		gpio_set_out(PCM1_CLK, DATA_HIGH);

		if(enable_data_out)
		{
			if(val_do & (1<<(PCM_BITS-i-1)))
			{
				gpio_set_out(PCM1_DO0, DATA_HIGH);
			}
			else
			{
				gpio_set_out(PCM1_DO0, DATA_LOW);
			}
		}

		udelay(3);
		
		gpio_set_out(PCM1_CLK, DATA_LOW);

		if(enable_data_in)
		{
			if(get_gpio_in_val(PCM1_DI) == 1)
			{
				val_di |= (1<<(PCM_BITS-i-1));
			}
			else
			{
				val_di &= ~(1<<(PCM_BITS-i-1));
			}
		}
		
		udelay(3);
	}

	return val_di;
}

static int pcm_slave_kthread(void *arg)
{
	int playbackofs = 0;
	int recordofs = 0;
	
	GPIOERR("pcm_slave_kthread start\n");
	while(1)
	{
		if(kthread_should_stop())
		{
			break;
		}

		if(isplaybackStart || isrecordStart)
		{
			recordbuf[recordw + recordofs] = handle_pcm_frame(playbackbuf[playbackr + playbackofs], isplaybackStart, isrecordStart);

			if(isplaybackStart)
			{
				playbackofs += 1;
				if(playbackofs >= PLAYBACK_PERIOD_SIZE)
				{
					playbackr = (playbackr + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE;
					playbackofs = 0;
				
					if(is_playbackbuf_empty())
					{
						//GPIOERR("is_playbackbuf_empty\n");
						isplaybackStart = 0;
					}
				
					if(ev_t == 0)
					{
						//GPIOERR("pcm_slave_kthread wake_up_interruptible\n");
						ev_t = 1;
						wake_up_interruptible(&waitq_t);
					}
				}
			}

			if(isrecordStart)
			{
				recordofs += 1;
				if(recordofs >= RECORD_PERIOD_SIZE)
				{
					recordw = (recordw + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE;
					recordofs = 0;
				
					if(is_recordbuf_full())
					{
						isrecordStart = 0;
					}
				
					if(ev_r == 0)
					{
						ev_r = 1;
						wake_up_interruptible(&waitq_r);
					}
					else
					{
						isrecordStart = 0;
					}
				}
			}
		}			
		else
		{
			//GPIOERR("pcm_slave_kthread mdelay\n");
			mdelay(50);
		}
	}

	GPIOERR("pcm_slave_kthread stop\n");
	return 0;
}
#endif

static void gpio_slave_init(void)
{
	gpio_regs = ioremap(0x10211000, 0x1000);
	GPIOERR("gpio_regs=0x%p\n", gpio_regs);
	
	//mt_set_gpio_mode(PCM1_CLK, GPIO_MODE_00);
	//mt_set_gpio_mode(PCM1_SYNC, GPIO_MODE_00);
	//mt_set_gpio_mode(PCM1_DI, GPIO_MODE_00);
	mt_set_gpio_mode(PCM1_DO0, GPIO_MODE_00);
	
	//gpio_set_dir(PCM1_CLK, DIR_OUT);
	//gpio_set_dir(PCM1_SYNC, DIR_OUT);
	//gpio_set_dir(PCM1_DI, DIR_IN);
	gpio_set_dir(PCM1_DO0, DIR_OUT);
	
	//gpio_set_out(PCM1_CLK, DATA_LOW);
	//gpio_set_out(PCM1_SYNC, DATA_LOW);
	gpio_set_out(PCM1_DO0, DATA_LOW);
}

static int pcm_slave_start(void)
{
	gpio_slave_init();
	//pcm_kthread = kthread_create(pcm_slave_kthread, NULL, "pcm_slave_kthread");
	//if (IS_ERR(pcm_kthread))
	//	return PTR_ERR(pcm_kthread);
	//wake_up_process(pcm_kthread);
	setplayback();
	setrecord();
	GPIOERR("pcm_start_init\n");
	return 0;
}

static int pcm_slave_read(void *arg)
{
	int ret;
	isrecordStart = 1;
	if(is_recordbuf_empty())
	{
		//GPIOERR("is_recordbuf_empty\n");
		ev_r = 0;
		wait_event_interruptible_timeout(waitq_r, ev_r, 5*HZ);//–›√ﬂ						
	}
	
	ret = copy_to_user(arg, recordbuf+recordr, RECORD_PERIOD_SIZE * FRAME_SIZE);
	recordr = (recordr + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE;
	return ret;
}

static int pcm_slave_write(void *arg)
{
	int ret;
	if(is_playbackbuf_full())
	{
		//GPIOERR("is_playbackbuf_full\n");
		ev_t = 0;
		wait_event_interruptible_timeout(waitq_t, ev_t, 5*HZ);//–›√ﬂ		
	}
	
	ret = copy_from_user(playbackbuf+playbackw, arg, PLAYBACK_PERIOD_SIZE * FRAME_SIZE);
	playbackw = (playbackw + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE;
	isplaybackStart=1;
	return ret;
}

static void pcm_slave_stop(void)
{
	if(pcm_kthread)
	{
		kthread_stop(pcm_kthread);
		pcm_kthread = NULL;
	}
	
	if(gpio_regs)
	{
		iounmap(gpio_regs);
		gpio_regs = NULL;
	}
	
	if(ev_t == 0)
	{
		GPIOERR("pcm_stop wake_up_interruptible ev_t\n");
		ev_t = 1;
		wake_up_interruptible(&waitq_t);
	}
	
	if(ev_r == 0)
	{
		GPIOERR("pcm_stop wake_up_interruptible ev_r\n");
		ev_r = 1;
		wake_up_interruptible(&waitq_r);
	}
	
	GPIOERR("pcm_stop\n");
}

static long pcm_slave_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{	
	switch(cmd)
	{
		case PCM_START:
		{
			return pcm_slave_start();
		}

		case PCM_STOP:
		{
			pcm_slave_stop();
			break;
		}
		
		case PCM_READ_PCM:
		{
			//GPIOERR("PCM_READ_PCM\n");
			return pcm_slave_read((void *)arg);
		}
		
		case PCM_WRITE_PCM:
		{
			//GPIOERR("PCM_WRITE_PCM\n");
			return pcm_slave_write((void *)arg);
		}

		default:break;
	}
	return 0;
}

static int pcm_slave_release(struct inode *inode, struct file *file)
{
	pcm_slave_stop();
	return 0;
}

static const struct file_operations pcm_slave_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = pcm_slave_ioctl,
	.release = pcm_slave_release,
};

static struct miscdevice pcm_slave_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "pcm_slave_gpio",
	.fops = &pcm_slave_fops,
};

static int irqtype;
static int pcmirq;
int cnt = 0;
static void pcm_slave_handler(unsigned long data)
{
	cnt++;
	if(irqtype == IRQF_TRIGGER_FALLING)
	{
		irq_set_irq_type(pcmirq, IRQF_TRIGGER_RISING);
		irqtype = IRQF_TRIGGER_RISING;
	}
	else
	{
		irq_set_irq_type(pcmirq, IRQF_TRIGGER_FALLING);
		irqtype = IRQF_TRIGGER_FALLING;
	}

	//enable_irq(pcmirq);
}

static DECLARE_TASKLET(pcm_slave_tasklet, pcm_slave_handler, 0);
static irqreturn_t pcm_slave_eint_interrupt_handler(int irq, void *dev_id)
{
	//static int i=0;
	//static int playbackofs = 0;
	//static int recordofs=0;
	//static unsigned short val_di=0;
	//static unsigned short val_do=0;
	//disable_irq_nosync(pcmirq);
	//tasklet_schedule(&pcm_slave_tasklet);
	pcm_slave_handler(0);
	//GPIOERR("pin=%d\n", get_gpio_in_val(PCM1_DI));	
	//if(cnt % 1000 == 0)
	//if(get_gpio_in_val(PCM1_CLK) == DATA_HIGH)
	//{
		//GPIOERR("DATA_HIGH pin=%d %d\n", get_gpio_in_val(PCM1_DI), cnt);	
	//}
	//else
	//{
		//GPIOERR("DATA_LOW pin=%d %d\n", get_gpio_in_val(PCM1_DI), cnt);	
	//}
#if 0
	if(get_gpio_in_val(PCM1_CLK) == DATA_HIGH)
	{
		//…œ…˝—ÿ ∑¢ ˝æ›
		if(val_do & (1<<(PCM_BITS-i-1)))
		{
			gpio_set_out(PCM1_DO0, DATA_HIGH);
		}
		else
		{
			gpio_set_out(PCM1_DO0, DATA_LOW);
		}
	}
	else
	{
		//œ¬Ωµ—ÿ ∂¡ ˝æ›
		if(get_gpio_in_val(PCM1_DI) == 1)
		{
			val_di |= (1<<(PCM_BITS-i-1));
		}
		else
		{
			val_di &= ~(1<<(PCM_BITS-i-1));
		}
	}

	++i;
	if(i == PCM_BITS)
	{
		i = 0;
		if(isplaybackStart)
		{
			playbackofs += 1;
			if(playbackofs >= PLAYBACK_PERIOD_SIZE)
			{
				playbackr = (playbackr + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE;
				playbackofs = 0;
			
				if(is_playbackbuf_empty())
				{
					//GPIOERR("is_playbackbuf_empty\n");
					isplaybackStart = 0;
				}
			
				if(ev_t == 0)
				{
					//GPIOERR("pcm_slave_eint_interrupt_handler wake_up_interruptible waitq_t\n");
					ev_t = 1;
					wake_up_interruptible(&waitq_t);
				}
			}
			
			val_do=playbackbuf[playbackr + playbackofs];
		}

		if(isrecordStart)
		{
			recordbuf[recordw + recordofs] = val_di;
			recordofs += 1;
			if(recordofs >= RECORD_PERIOD_SIZE)
			{
				recordw = (recordw + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE;
				recordofs = 0;
			
				if(is_recordbuf_full())
				{
					//GPIOERR("is_recordbuf_full\n");
					isrecordStart = 0;
				}
			
				if(ev_r == 0)
				{
					//GPIOERR("pcm_slave_eint_interrupt_handler wake_up_interruptible waitq_r\n");
					ev_r = 1;
					wake_up_interruptible(&waitq_r);
				}
				else
				{
					isrecordStart = 0;
				}
			}
		}
	}
#endif

	return IRQ_HANDLED;
}

static int pcm_slave_kthread(void *arg)
{
	int i=16;
	int j=8000;
	GPIOERR("pcm_slave_kthread start\n");
	mdelay(1000);
	while(j>0)
	{
		--j;
		while(i>0)
		{
			if(kthread_should_stop())
			{
				break;
			}
		
			--i;
			gpio_set_out(PCM1_DO0, DATA_LOW);
			udelay(1);//GPIOERR("pin=%d\n", get_gpio_in_val(PCM1_DI));
			gpio_set_out(PCM1_DO0, DATA_HIGH);
			udelay(1);//GPIOERR("pin=%d\n", get_gpio_in_val(PCM1_DI));
		}

		udelay(50);
		i=16;
	}


	GPIOERR("pcm_slave_kthread exit  cnt %d\n", cnt);
	pcm_kthread = NULL;
	return 0;
}

void __iomem *clk_audio_base = NULL;
struct resource *regs;
static int pcm_slave_probe(struct platform_device *pdev)
{	
	clk_audio_base = ioremap(0x11220048, 0x1000);

	if(clk_audio_base == NULL)GPIOERR("[CLK_AUDIO] base error\n");
	else
	GPIOERR("[CLK_AUDIO1] base 0x%p\n", clk_audio_base);
	GPIOERR("[CLK_AUDIO2] base 0x%.8x\n", *(const volatile u32 __force *)clk_audio_base);

	*(volatile u32 __force *)clk_audio_base = 0X1; 
	GPIOERR("[CLK_AUDIO3] base 0x%.8x\n", *(const volatile u32 __force *)clk_audio_base);
	return 0;
}

static int pcm_slave_remove(struct platform_device *pdev)
{	
	iounmap(clk_audio_base);
	//release_mem_region(regs->start, resource_size(regs));
	return 0;
}

static const struct of_device_id pcm_slave_of_match[] = {
	{.compatible = "mediatek,mt6735-audiosys"},
	{},
};

static struct platform_driver pcm_slave_drv = {
	.probe = pcm_slave_probe,
	.remove = pcm_slave_remove,
	.driver = {
		   .name = "pcm_slave_gpio",
		   .owner = THIS_MODULE,
		   .of_match_table = pcm_slave_of_match,
		   },
};

static int pcm_slave_init(void)
{
	return platform_driver_register(&pcm_slave_drv);
}

static void pcm_slave_exit(void)
{
	platform_driver_unregister(&pcm_slave_drv);
}

module_init(pcm_slave_init);
module_exit(pcm_slave_exit);
MODULE_LICENSE("GPL");
