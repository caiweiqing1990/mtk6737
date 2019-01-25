#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h> 
#include <linux/serial.h>
#include <linux/ioctl.h>

#define GPIO_IOC_MAGIC 0x90

#define GPIO_IOCQMODE           _IOR(GPIO_IOC_MAGIC, 0x01, uint32_t)
#define GPIO_IOCTMODE0          _IOW(GPIO_IOC_MAGIC, 0x02, uint32_t)
#define GPIO_IOCTMODE1          _IOW(GPIO_IOC_MAGIC, 0x03, uint32_t)
#define GPIO_IOCTMODE2          _IOW(GPIO_IOC_MAGIC, 0x04, uint32_t)
#define GPIO_IOCTMODE3          _IOW(GPIO_IOC_MAGIC, 0x05, uint32_t)
#define GPIO_IOCQDIR            _IOR(GPIO_IOC_MAGIC, 0x06, uint32_t)
#define GPIO_IOCSDIRIN          _IOW(GPIO_IOC_MAGIC, 0x07, uint32_t)
#define GPIO_IOCSDIROUT         _IOW(GPIO_IOC_MAGIC, 0x08, uint32_t)
#define GPIO_IOCQPULLEN         _IOR(GPIO_IOC_MAGIC, 0x09, uint32_t)
#define GPIO_IOCSPULLENABLE     _IOW(GPIO_IOC_MAGIC, 0x0A, uint32_t)
#define GPIO_IOCSPULLDISABLE    _IOW(GPIO_IOC_MAGIC, 0x0B, uint32_t)
#define GPIO_IOCQPULL           _IOR(GPIO_IOC_MAGIC, 0x0C, uint32_t)
#define GPIO_IOCSPULLDOWN       _IOW(GPIO_IOC_MAGIC, 0x0D, uint32_t)
#define GPIO_IOCSPULLUP         _IOW(GPIO_IOC_MAGIC, 0x0E, uint32_t)
#define GPIO_IOCQINV            _IOR(GPIO_IOC_MAGIC, 0x0F, uint32_t)
#define GPIO_IOCSINVENABLE      _IOW(GPIO_IOC_MAGIC, 0x10, uint32_t)
#define GPIO_IOCSINVDISABLE     _IOW(GPIO_IOC_MAGIC, 0x11, uint32_t)
#define GPIO_IOCQDATAIN         _IOR(GPIO_IOC_MAGIC, 0x12, uint32_t)
#define GPIO_IOCQDATAOUT        _IOR(GPIO_IOC_MAGIC, 0x13, uint32_t)
#define GPIO_IOCSDATALOW        _IOW(GPIO_IOC_MAGIC, 0x14, uint32_t)
#define GPIO_IOCSDATAHIGH       _IOW(GPIO_IOC_MAGIC, 0x15, uint32_t)

int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3){
		printf("%s gpio_num\n", argv[0]);
		printf("%s gpio_num val\n", argv[0]);
		return 0;
	}
	
	int fd = open("/dev/mtgpio",O_RDWR | O_NONBLOCK);
	if(fd<0)
	{
		printf("cann't open /dev/mtgpio\n");
		return -1;
	}
	
	int	pin = atoi(argv[1]);
	printf("pin=%d\n", pin);
	
	int	op = GPIO_IOCTMODE0;
	ioctl(fd, op, pin);
	
	if(argc == 3)
	{
		op = GPIO_IOCSDIROUT;//输出
		ioctl(fd, op, pin);	

		int	val = atoi(argv[2]);
		
		if(val == 0)
		{
			op = GPIO_IOCSDATALOW;
			ioctl(fd, op, pin);
			
			op = GPIO_IOCQDATAOUT;
			printf("DATAOUT=%d\n", ioctl(fd, op, pin));
		}
		else
		{
			op = GPIO_IOCSDATAHIGH;
			ioctl(fd, op, pin);
			
			op = GPIO_IOCQDATAOUT;
			printf("DATAOUT=%d\n", ioctl(fd, op, pin));
		}
	}
	else
	{
		op = GPIO_IOCSDIRIN;//输入
		ioctl(fd, op, pin);
		
		op = GPIO_IOCQDATAIN;
		printf("DATAIN=%d\n", ioctl(fd, op, pin));
	}
	
	
}

