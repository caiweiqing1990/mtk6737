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

#include "gpio_cfg.h"

#define GPIOTAG                "PCM_MASTER"
#define GPIOLOG(fmt, arg...)   pr_debug(GPIOTAG fmt, ##arg)
#define GPIOMSG(fmt, arg...)   pr_warn(fmt, ##arg)
#define GPIOERR(fmt, arg...)   pr_err(GPIOTAG "===================================%5d: "fmt, __LINE__, ##arg)

#define DATA_LOW			0
#define DATA_HIGH			1
#define DIR_IN				0
#define DIR_OUT				1

#define PCM_IOC_MAGIC 0x80

#define PCM_START           _IO(PCM_IOC_MAGIC, 0x01)
#define PCM_READ_PCM        _IOR(PCM_IOC_MAGIC, 0x02, uint32_t)
#define PCM_WRITE_PCM       _IOW(PCM_IOC_MAGIC, 0x03, uint32_t)
#define PCM_STOP          	_IO(PCM_IOC_MAGIC, 0x04)

#define	PCM1_CLK			61
#define	PCM1_SYNC			62
#define	PCM1_DI				63
#define	PCM1_DO0			64

#define	PCM2_CLK			48
#define	PCM2_SYNC			47
#define	PCM2_DI				51
#define	PCM2_DO0			52

#define PCM_BITS			16
#define PCM_RATE			8000
#define PCM_CHANNAL			1

#define GPIO_MODE_00		0

static void __iomem *gpio_regs = NULL;
static struct task_struct *pcm_kthread;

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

void DELAY(void)
{
	ndelay(500);ndelay(500);ndelay(250);ndelay(50);
	//udelay(3);
}
static unsigned short handle_pcm_frame(unsigned short val_do, int enable_data_out, int enable_data_in)
{
	int i,j;
	unsigned short val_di=0;
	
	gpio_set_out(PCM1_SYNC, DATA_HIGH);
	gpio_set_out(PCM1_CLK, DATA_HIGH);
	
	DELAY();
	gpio_set_out(PCM1_CLK, DATA_LOW);
	DELAY();
	gpio_set_out(PCM1_SYNC, DATA_LOW);
	for(j=0;j<2;j++)
	{
		for(i=0; i<PCM_BITS; i++)
		{
			gpio_set_out(PCM1_CLK, DATA_HIGH);
			if(enable_data_out)
			{
				if(val_do & (1<<(PCM_BITS-1)))
				{
					gpio_set_out(PCM1_DO0, DATA_HIGH);
				}
				else
				{
					gpio_set_out(PCM1_DO0, DATA_LOW);
				}
				val_do = val_do << 1;
			}
			DELAY();
			gpio_set_out(PCM1_CLK, DATA_LOW);
			if(enable_data_in)
			{
				if(get_gpio_in_val(PCM1_DI) == 1)
				{
					if(j == 0)val_di |= (1<<(PCM_BITS-i-1));
				}
				else
				{
					if(j == 0)val_di &= ~(1<<(PCM_BITS-i-1));
				}
			}	
			DELAY();
		}
	}
	return val_di;
}

static int pcm_master_kthread(void *arg)
{
	int playbacksize = 0;
	int recordsize = 0;
	
	GPIOERR("pcm_master_kthread start\n");
	while(1)
	{
		if(kthread_should_stop())
		{
			break;
		}

		if(isplaybackStart || isrecordStart)
		{
			recordbuf[recordw + recordsize] = handle_pcm_frame(playbackbuf[playbackr + playbacksize], isplaybackStart, isrecordStart);

			if(isplaybackStart)
			{
				playbacksize += 1;
				if(playbacksize >= PLAYBACK_PERIOD_SIZE)
				{
					playbackr = (playbackr + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE;
					playbacksize = 0;
				
					if(is_playbackbuf_empty())
					{
						//GPIOERR("is_playbackbuf_empty\n");
						isplaybackStart = 0;
					}
				
					if(ev_t == 0)
					{
						//GPIOERR("pcm_master_kthread wake_up_interruptible\n");
						ev_t = 1;
						wake_up_interruptible(&waitq_t);
					}
				}
			}

			if(isrecordStart)
			{
				recordsize += 1;
				if(recordsize >= RECORD_PERIOD_SIZE)
				{
					recordw = (recordw + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE;
					recordsize = 0;
				
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
			//GPIOERR("pcm_master_kthread mdelay\n");
			mdelay(50);
		}
	}

	GPIOERR("pcm_master_kthread stop\n");
	return 0;
}

static void gpio_init(void)
{	
	gpio_regs = ioremap(0x10211000, 0x1000);
	GPIOERR("gpio_regs=0x%p\n", gpio_regs);
	
	mt_set_gpio_mode(PCM1_CLK, GPIO_MODE_00);
	mt_set_gpio_mode(PCM1_SYNC, GPIO_MODE_00);
	mt_set_gpio_mode(PCM1_DI, GPIO_MODE_00);
	mt_set_gpio_mode(PCM1_DO0, GPIO_MODE_00);
	
	gpio_set_dir(PCM1_CLK, DIR_OUT);
	gpio_set_dir(PCM1_SYNC, DIR_OUT);
	gpio_set_dir(PCM1_DI, DIR_IN);
	gpio_set_dir(PCM1_DO0, DIR_OUT);
	
	gpio_set_out(PCM1_CLK, DATA_LOW);
	gpio_set_out(PCM1_SYNC, DATA_LOW);
	gpio_set_out(PCM1_DO0, DATA_LOW);
}

static int pcm_master_start_init(void)
{
	gpio_init();
	pcm_kthread = kthread_create(pcm_master_kthread, NULL, "pcm_master_kthread");
	if (IS_ERR(pcm_kthread))
		return PTR_ERR(pcm_kthread);
	wake_up_process(pcm_kthread);
	setplayback();
	setrecord();
	GPIOERR("pcm_master_start_init\n");
	return 0;
}

static int pcm_master_read(void *arg)
{
	int ret;
	isrecordStart = 1;
	if(is_recordbuf_empty())
	{
		//GPIOERR("is_recordbuf_empty\n");
		ev_r = 0;
		wait_event_interruptible(waitq_r, ev_r);//–›√ﬂ						
	}
	
	ret = copy_to_user(arg, recordbuf+recordr, RECORD_PERIOD_SIZE * FRAME_SIZE);
	recordr = (recordr + RECORD_PERIOD_SIZE)%RECORD_BUF_SIZE;
	return ret;
}

static int pcm_master_write(void *arg)
{
	int ret;
	if(is_playbackbuf_full())
	{
		//GPIOERR("is_playbackbuf_full\n");
		ev_t = 0;
		wait_event_interruptible(waitq_t, ev_t);//–›√ﬂ		
	}
	
	ret = copy_from_user(playbackbuf+playbackw, arg, PLAYBACK_PERIOD_SIZE * FRAME_SIZE);
	playbackw = (playbackw + PLAYBACK_PERIOD_SIZE)%PLAYBACK_BUF_SIZE;
	isplaybackStart=1;
	return ret;
}

static void pcm_master_stop(void)
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
		GPIOERR("pcm_master_stop wake_up_interruptible ev_t\n");
		ev_t = 1;
		wake_up_interruptible(&waitq_t);
	}
	
	if(ev_r == 0)
	{
		GPIOERR("pcm_master_stop wake_up_interruptible ev_r\n");
		ev_r = 1;
		wake_up_interruptible(&waitq_r);
	}
	
	GPIOERR("pcm_master_stop\n");
}

static long pcm_master_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{	
	switch(cmd)
	{
		case PCM_START:
		{
			return pcm_master_start_init();
		}

		case PCM_STOP:
		{
			pcm_master_stop();
			break;
		}
		
		case PCM_READ_PCM:
		{
			//GPIOERR("PCM_READ_PCM\n");
			return pcm_master_read((void *)arg);
		}
		
		case PCM_WRITE_PCM:
		{
			//GPIOERR("PCM_WRITE_PCM\n");
			return pcm_master_write((void *)arg);
		}

		default:break;
	}
	return 0;
}

static int pcm_master_release(struct inode *inode, struct file *file)
{
	GPIOERR("pcm_master_release\n");
	pcm_master_stop();
	return 0;
}

static const struct file_operations pcm_master_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = pcm_master_ioctl,
	.release = pcm_master_release,
};

static struct miscdevice pcm_master_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "pcm_master_gpio",
	.fops = &pcm_master_fops,
};

static int pcm_master_init(void)
{
	int err;

	recordbuf = kmalloc(RECORD_BUF_SIZE * FRAME_SIZE, GFP_KERNEL);
	if(recordbuf == NULL)
	{
		GPIOERR("recordbuf kmalloc error\n");
		return -ENOMEM;
	}
	
	playbackbuf = kmalloc(PLAYBACK_BUF_SIZE * FRAME_SIZE, GFP_KERNEL);
	if(playbackbuf == NULL)
	{
		GPIOERR("playbackbuf kmalloc error\n");
		return -ENOMEM;
	}
	
	err = misc_register(&pcm_master_device);
	if (err)
		GPIOERR("misc_register pcm_master_device error\n");
	
	return 0;
}

static void pcm_master_exit(void)
{
	int err;
	kfree(recordbuf);
	kfree(playbackbuf);
	err = misc_deregister(&pcm_master_device);
	if (err)
		GPIOERR("misc_deregister pcm_master_device error\n");
}

module_init(pcm_master_init);
module_exit(pcm_master_exit);
MODULE_LICENSE("GPL");
