#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define PCM_IOC_MAGIC 0x80

#define PCM_START           _IO(PCM_IOC_MAGIC, 0x01)
#define PCM_READ_PCM        _IOR(PCM_IOC_MAGIC, 0x02, uint32_t)
#define PCM_WRITE_PCM       _IOW(PCM_IOC_MAGIC, 0x03, uint32_t)
#define PCM_STOP          	_IO(PCM_IOC_MAGIC, 0x04)

int fdr;
int pcmfd;
int fdw;

static void *test(void *p)
{
	char buf1[3200]={0};
	int ret;
	while(1)
	{
		ret=read(fdr, buf1, 3200);
		if(ret != 3200)
		{
			break;
		}
		printf("PCM_WRITE_PCM\n");
		ioctl(pcmfd, PCM_WRITE_PCM, buf1);		
	}
	printf("test quit\n");
	return NULL;
}

static void *test1(void *p)
{
	int i=0;
	char buf2[3200]={0};
	
	while(i<30)
	{	
		i++;
		printf("PCM_READ_PCM\n");
		if(ioctl(pcmfd, PCM_READ_PCM, buf2) < 0)
			break;
		write(fdw, buf2, 3200);	
	}
	printf("test1 quit\n");
	exit(1);
	return NULL;
}

int main(int argc, char **argv)
{
 	if (argc != 3)
	{
		printf("%s in.raw out.raw\n", argv[0]);
		return -1;
	}

	int ret;

	pcmfd = open("/dev/pcm_master_gpio", O_RDWR);
	if(pcmfd < 0)
	{
		printf("can't open /dev/pcm_master_gpio\n");
		return -1;
	}
	
	fdr = open(argv[1], O_RDWR);
	if (fdr < 0)
	{
		printf("can't open %s\n", argv[1]);
		return -1;
	}
	
	fdw = open(argv[2], O_RDWR|O_CREAT, 0666);
	if (fdw < 0)
	{
		printf("can't open %s\n", argv[2]);
		return -1;
	}
	
	printf("PCM_START\n");
	ioctl(pcmfd, PCM_START, 0);
	
	pthread_t id_8;
	if(pthread_create(&id_8, NULL, test, NULL) == -1) exit(1);
	pthread_t id_7;
	if(pthread_create(&id_7, NULL, test1, NULL) == -1) exit(1);
	
	
	while(1)
	{	
		sleep(1);
	}
	
	printf("PCM_STOP\n");
	ioctl(pcmfd, PCM_STOP, 0);
	close(pcmfd);
	close(fdr);
	close(fdw);
	return 0; 	
}