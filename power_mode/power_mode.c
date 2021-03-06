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
#include <time.h>

typedef enum {
    HW_GPIO0=0,   HW_GPIO1,    HW_GPIO2,     HW_GPIO3, 
    HW_GPIO4,     HW_GPIO5,    HW_GPIO6,     HW_GPIO7, 
    HW_GPIO8,     HW_GPIO9,    HW_GPIO10,    HW_GPIO11, 
    HW_GPIO12,    HW_GPIO13,   HW_GPIO14,    HW_GPIO15,
    HW_GPIO16,    HW_GPIO17,   HW_GPIO18,    HW_GPIO19,
    HW_GPIO20,    HW_GPIO21,   HW_GPIO22,    HW_GPIO23,
    HW_GPIO24,    HW_GPIO25,   HW_GPIO26,    HW_GPIO27,
    HW_GPIO28,    HW_GPIO29,   HW_GPIO30,    HW_GPIO31,
    HW_GPIO32,    HW_GPIO33,   HW_GPIO34,    HW_GPIO35,
    HW_GPIO36,    HW_GPIO37,   HW_GPIO38,    HW_GPIO39,
    HW_GPIO40,    HW_GPIO41,   HW_GPIO42,    HW_GPIO43,
    HW_GPIO44,    HW_GPIO45,   HW_GPIO46,    HW_GPIO47,
    HW_GPIO48,    HW_GPIO49,   HW_GPIO50,    HW_GPIO51,
    HW_GPIO52,    HW_GPIO53,   HW_GPIO54,    HW_GPIO55,
    HW_GPIO56,    HW_GPIO57,   HW_GPIO58,    HW_GPIO59,
    HW_GPIO60,    HW_GPIO61,   HW_GPIO62,    HW_GPIO63,
    HW_GPIO64,    HW_GPIO65,   HW_GPIO66,    HW_GPIO67,
    HW_GPIO68,    HW_GPIO69,   HW_GPIO70,    HW_GPIO71,
    HW_GPIO72,    HW_GPIO73,   HW_GPIO74,    HW_GPIO75,
    HW_GPIO76,    HW_GPIO77,   HW_GPIO78,    HW_GPIO79,
    HW_GPIO80,    HW_GPIO81,   HW_GPIO82,    HW_GPIO83,
    HW_GPIO84,    HW_GPIO85,   HW_GPIO86,    HW_GPIO87,
    HW_GPIO88,    HW_GPIO89,   HW_GPIO90,    HW_GPIO91,
    HW_GPIO92,    HW_GPIO93,   HW_GPIO94,    HW_GPIO95,
    HW_GPIO96,    HW_GPIO97,   HW_GPIO98,    HW_GPIO99,
    HW_GPIO100,   HW_GPIO101,  HW_GPIO102,   HW_GPIO103,
    HW_GPIO104,   HW_GPIO105,  HW_GPIO106,   HW_GPIO107,
    HW_GPIO108,   HW_GPIO109,  HW_GPIO110,   HW_GPIO111,    
    HW_GPIO112,   HW_GPIO113,  HW_GPIO114,   HW_GPIO115,
    HW_GPIO116,   HW_GPIO117,  HW_GPIO118,   HW_GPIO119,
    HW_GPIO120,   HW_GPIO121,  HW_GPIO122,   HW_GPIO123,
    HW_GPIO124,   HW_GPIO125,  HW_GPIO126,   HW_GPIO127,
    HW_GPIO128,   HW_GPIO129,  HW_GPIO130,   HW_GPIO131,
    HW_GPIO132,   HW_GPIO133,  HW_GPIO134,   HW_GPIO135,
    HW_GPIO136,   HW_GPIO137,  HW_GPIO138,   HW_GPIO139,
    HW_GPIO140,   HW_GPIO141,  HW_GPIO142,   HW_GPIO143,
    HW_GPIO144,   HW_GPIO145,  HW_GPIO146,   
    HW_GPIO_MAX
} HW_GPIO;

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

#define MSM_POWER		HW_GPIO3
#define PWREN			HW_GPIO127
#define RESET_IN		HW_GPIO122
#define USB_BOOT		HW_GPIO120

#define AP_WAKEUP_BB	HW_GPIO123
#define BB_WAKEUPAP		HW_GPIO124
#define AP_SLEEP_BB		HW_GPIO121
#define BB_SLEEP_AP		HW_GPIO98

void gpio_out(int pin, int val)
{
	int fd = open("/dev/mtgpio", O_RDONLY);
	ioctl(fd, GPIO_IOCTMODE0, pin);			//配置为GPIO模式
	ioctl(fd, GPIO_IOCSDIROUT, pin);		//配置为输出模式
	if(val == 0)
		ioctl(fd, GPIO_IOCSDATALOW, pin);	//输出低电平
	else
		ioctl(fd, GPIO_IOCSDATAHIGH, pin);	//输出高电平
	close(fd);
}

void gpio_pull_disable(int gpio)
{
	int fd = open("/dev/mtgpio", O_RDONLY);
	ioctl(fd, GPIO_IOCSPULLDISABLE, gpio);
	close(fd);
}

void msm01a_on(void)
{
	gpio_out(MSM_POWER, 1);
	gpio_out(AP_WAKEUP_BB, 0);
	gpio_out(AP_SLEEP_BB, 0);
	gpio_out(USB_BOOT, 1);
	sleep(1);
	gpio_out(PWREN, 1);
	sleep(1);
	gpio_out(RESET_IN, 1);
}

void msm01a_reset(void)
{
	gpio_out(PWREN, 1);
	gpio_out(RESET_IN, 0);
	sleep(1);
	gpio_out(RESET_IN, 1);
}

void msm01a_off(void)
{
	gpio_out(PWREN, 0);
	gpio_out(RESET_IN, 1);
	sleep(1);
	gpio_out(RESET_IN, 0);
	gpio_out(MSM_POWER, 0);
	sleep(1);
}

//用于天通升级切换为U盘
void msm01a_ap(void)
{
	gpio_out(HW_GPIO120, 0);
	msm01a_reset();
}

void print_usage(char *file)
{
	printf("Usage:\n");
	printf("%s msm01a reset\n", file);
	printf("%s msm01a on\n", file);
	printf("%s msm01a off\n", file);
	printf("%s msm01a ap\n", file);
}

int main(int argc, char **argv)
{
	if (argc != 3){
		print_usage(argv[0]);
		return 0;
	}
	
	if(!strcmp("msm01a", argv[1])){
		if (!strcmp("reset", argv[2])){
			msm01a_reset();
		}
		else if (!strcmp("on", argv[2])){
			msm01a_on();
		}
		else if (!strcmp("off", argv[2])){
			msm01a_off();
		}
		else if (!strcmp("ap", argv[2])){
			msm01a_ap();
		}
		else{
			print_usage(argv[0]);
			return 0;
		}
	}
	else{
		print_usage(argv[0]);
		return 0;
	}
	
}
