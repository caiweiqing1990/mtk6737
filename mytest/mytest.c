#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>   /* signal() */
#include <fcntl.h> /* file control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h> /* 注意此处：signal.h要先include进来 */
#include <ctype.h>
#include <sys/select.h> /* select() */
#include <threads.h>

static int getBaudrate(int baudrate)
{
	switch(baudrate) 
	{
		case 0: return B0;
		case 50: return B50;
		case 75: return B75;
		case 110: return B110;
		case 134: return B134;
		case 150: return B150;
		case 200: return B200;
		case 300: return B300;
		case 600: return B600;
		case 1200: return B1200;
		case 1800: return B1800;
		case 2400: return B2400;
		case 4800: return B4800;
		case 9600: return B9600;
		case 19200: return B19200;
		case 38400: return B38400;
		case 57600: return B57600;
		case 115200: return B115200;
		case 230400: return B230400;
		case 460800: return B460800;
		case 500000: return B500000;
		case 576000: return B576000;
		case 921600: return B921600;
		case 1000000: return B1000000;
		case 1152000: return B1152000;
		case 1500000: return B1500000;
		case 2000000: return B2000000;
		case 2500000: return B2500000;
		case 3000000: return B3000000;
		case 3500000: return B3500000;
		case 4000000: return B4000000;
		default: return -1;
	}
}

int init_serial(int *fd, char *device, int baud_rate)
{
	printf("open serial port : %s ...\n", device);
	int fd_serial = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd_serial < 0)
	{
		perror("open fd_serial");
		return -1;
	}
	*fd = fd_serial;
	/* 串口主要设置结构体termios <termios.h> */
	struct termios options;

	/* 1.tcgetattr()用于获取与终端相关的参数
	*   参数fd为终端的文件描述符，返回的结果保存在termios结构体中
	*/
	tcgetattr(fd_serial, &options);
	baud_rate = getBaudrate(baud_rate);
	/* 2.修改获得的参数 */
	options.c_cflag |= CLOCAL | CREAD; /* 设置控制模块状态：本地连接，接收使能 */
	options.c_cflag &= ~CSIZE;         /* 字符长度，设置数据位之前，一定要屏蔽这一位 */
	//options.c_cflag &= ~CRTSCTS;       /* 无硬件流控 */
	options.c_cflag |= CRTSCTS;       /* 硬件流控 */
	options.c_cflag |= CS8;            /* 8位数据长度 */
	options.c_cflag &= ~CSTOPB;        /* 1位停止位 */
	options.c_iflag |= IGNPAR;         /* 无奇偶校验 */
	options.c_oflag = 0;               /* 输出模式 */
	options.c_lflag = 0;               /* 不激活终端模式 */
	cfsetospeed(&options, baud_rate);    /* 设置波特率 */
	/* 3.设置新属性: TCSANOW，所有改变立即生效 */
	tcflush(fd_serial, TCIFLUSH);      /* 溢出数据可以接收，但不读 */
	tcsetattr(fd_serial, TCSANOW, &options);
	printf("open serial port : %s successfully!!!\n", device);
	return 0;
}

int satfd = 0;
int flag = 0;
static void *func_xx(void *p)
{
  fd_set fds;
  FD_SET(satfd,&fds);
  char data[1024]={0};
  int  idx=0;
  int  n,i,flg=0,ncnt=0;
  
  while(1)
  {
      switch(select(satfd+1, &fds, NULL, NULL, NULL))
      {
        case -1:break;
        case  0:break;
        default:
			if (FD_ISSET(satfd, &fds))
			{
#if 0				
				n = read(satfd, data, 1024);
				data[n] = 0;
				printf("%d %s\n", n, data);
#else				
				while(1)
				{
				  if(idx==0)
				  {
					memset(data,0,1024);
					flg=0;
					ncnt=0;
				  }
				  n = read(satfd, &data[idx], 1);
				  
				  if(n>0)
				  {					
					if(data[idx]=='\r') data[idx]='\n';

					if(data[idx]=='\n') ncnt++;
					else ncnt = 0;

					if(ncnt==4)
					{
					  idx=2;
					  flg=0;
					  ncnt=0;
					  continue;
					}

					idx++;

					if(idx==1 && data[0] != '\n')
					{
					  idx = 0;
					  continue;
					}
					else if(idx==2 && data[1] != '\n')
					{
					  idx = 0;
					  continue;
					}
					else if(idx==3 && data[2] == '\n')
					{
					  idx = 2;
					  continue;
					}
					else if(idx>4)
					{
					  data[idx] = 0;
					  printf("%s", data);
					  if(strstr(data,"\n\nOK\n\n"))
					  {
						  if(data[idx-2]=='\n' && data[idx-1]=='\n')
						  {
							//printf("%s\n", data);	  
						  }
					  }
					  else if(strstr(data,"+CMT"))
					  {
						 if(data[idx-3]=='\n' && data[idx-2]=='\n' && data[idx-1]=='\n')
						  {
							 static int i=0;
							 i++;
							printf("%d %d %d %s",i, idx, strlen(data), data);	  
						  }
					  }

					}
				  }
				  else
				  {
					break;
				  }
				}
#endif
			}
      }
  }
}

int uart_send(int fd, char *data, int datalen)
{
  int len = 0;
  len = write(fd, data, datalen); /* 实际写入的长度 */
  if (len == datalen)
  {
    return len;
  }
  else
  {
    tcflush(fd, TCOFLUSH); /* TCOFLUSH，刷新写入的数据，但不传送 */
    return -1;
  }

  return 0;
}

/* 串口接收数据 */
int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("mytest /dev/ttySAT0 115200 AT\n");
		return -1;
	}
	
	int baud_rate = atoi(argv[2]);
	init_serial(&satfd, argv[1], baud_rate);
	if(satfd == 0)
		return 0;
	
	printf("satfd = %d baud_rate=%d\n",satfd, baud_rate);
	pthread_t thread_checksat;
	pthread_create(&thread_checksat, NULL, func_xx, NULL);
	char buf[1024]={0};
	int len;
	sleep(1);
	
	if(argc == 4)
	{
		//printf("%s %d\n", argv[3], strlen(argv[3]));
		sprintf(buf,"%s\r", argv[3]);
		printf("buf=%s\n", buf);
		printf("buf=%d\n", strlen(buf));
		uart_send(satfd, buf, strlen(buf));		
	}
	else if(argc == 5)
	{
		sprintf(buf,"%s", argv[4]);
		printf("buf=%s\n", buf);
		printf("buf=%d\n", strlen(buf));
		uart_send(satfd, buf, strlen(buf));	
		
		buf[0] = 0X1A;
		uart_send(satfd, buf, 1);
	}
	
	//while(1)
	{
		sleep(1);
	}
	return 0;
}
