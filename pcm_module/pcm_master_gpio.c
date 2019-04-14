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

#define	PCM1_CLK			61
#define	PCM1_SYNC			62
#define	PCM1_DI				63
#define	PCM1_DO0			64

#define GPIO_MODE_00		0

static void __iomem *gpio_regs = NULL;
static struct task_struct *pcm_kthread;

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
	int i=0;
	//for(i=0;i<18;i++)
	//	ndelay(1);
	for(i=0;i<844;i++)
		cpu_relax();
}

static int pcm_master_kthread(void *arg)
{
	GPIOERR("pcm_master_kthread start\n");
	while(1)
	{
		if(kthread_should_stop())
		{
			break;
		}
		gpio_set_out(PCM1_CLK, DATA_HIGH);
		DELAY();
		gpio_set_out(PCM1_CLK, DATA_LOW);
		DELAY();
	}

	GPIOERR("pcm_master_kthread stop\n");
	return 0;
}

static void gpio_init(void)
{	
	gpio_regs = ioremap(0x10211000, 0x1000);
	GPIOERR("gpio_regs=0x%p\n", gpio_regs);
	
	mt_set_gpio_mode(PCM1_CLK, GPIO_MODE_00);
	//mt_set_gpio_mode(PCM1_SYNC, GPIO_MODE_00);
	//mt_set_gpio_mode(PCM1_DI, GPIO_MODE_00);
	//mt_set_gpio_mode(PCM1_DO0, GPIO_MODE_00);
	
	gpio_set_dir(PCM1_CLK, DIR_OUT);
	//gpio_set_dir(PCM1_SYNC, DIR_OUT);
	//gpio_set_dir(PCM1_DI, DIR_IN);
	//gpio_set_dir(PCM1_DO0, DIR_OUT);
	
	gpio_set_out(PCM1_CLK, DATA_LOW);
	//gpio_set_out(PCM1_SYNC, DATA_LOW);
	//gpio_set_out(PCM1_DO0, DATA_LOW);
}

static int pcm_master_start_init(void)
{
	gpio_init();
	pcm_kthread = kthread_create(pcm_master_kthread, NULL, "pcm_master_kthread");
	if (IS_ERR(pcm_kthread))
		return PTR_ERR(pcm_kthread);
	wake_up_process(pcm_kthread);
	GPIOERR("pcm_master_start_init\n");
	return 0;
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
	
	GPIOERR("pcm_master_stop\n");
}

static int pcm_master_init(void)
{
	pcm_master_start_init();
	return 0;
}

static void pcm_master_exit(void)
{
	pcm_master_stop();
}

module_init(pcm_master_init);
module_exit(pcm_master_exit);
MODULE_LICENSE("GPL");
