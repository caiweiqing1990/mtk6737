#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gsmmux.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

//CONFIG_N_GSM
//cat /proc/devices | grep gsmtty | awk '{print $1}

#define N_GSM0710		21	/* GSM 0710 Mux */
#define DEFAULT_SPEED	B115200
#define SERIAL_PORT		"/dev/ttyMT1"

int main(int argc, char *argv[])
{
	int val;
	int ldisc = N_GSM0710;
	struct gsm_config c;
	struct termios configuration;

	struct termios options;
	
	/* open the serial port connected to the modem */
	int fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
	
	/* configure the serial port : speed, flow control ... */

	/* send the AT commands to switch the modem to CMUX mode
	   and check that it's successful (should return OK) */
	//write(fd, "AT+CMUX=0,0,5,1600\r", 19);

	/* experience showed that some modems need some time before
	   being able to answer to the first MUX packet so a delay
	   may be needed here in some case */
	//sleep(3);

	if(argc == 1)
	{
		/* use n_gsm line discipline */
		ioctl(fd, TIOCGETD, &val);
		
		if(val == N_GSM0710)
			return 0;
		
		ioctl(fd, TIOCSETD, &ldisc);

		/* get n_gsm configuration */
		ioctl(fd, GSMIOC_GETCONF, &c);
		/* we are initiator and need encoding 0 (basic) */
		c.initiator = 1;
		c.encapsulation = 0;
		/* our modem defaults to a maximum size of 1500 bytes */
		c.mru = 1500;
		c.mtu = 1500;
		/* set the new configuration */
		ioctl(fd, GSMIOC_SETCONF, &c);		
		/* and wait for ever to keep the line discipline enabled */
		daemon(0,0);
		pause();	
	}
	else
	{
		val = 0;
		ioctl(fd, TIOCSETD, &val);
		
		ioctl(fd, GSMIOC_GETCONF, &c);
		c.initiator = 0;
		c.encapsulation = 1;
		/* our modem defaults to a maximum size of 127 bytes */
		c.mru = 64;
		c.mtu = 64;
		ioctl(fd, GSMIOC_SETCONF, &c);	
	}
	
	return 0;
}