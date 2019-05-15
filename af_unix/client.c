#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/un.h>

void usage(char *s)
{
	printf("Usage: %s <unix_domaun_file>\n",s);
}

int main(int argc, const char *argv[])
{
	int fd;
	if(argc != 2)
	{
		usage((char *)argv[0]);
		exit(1);
	}
	
	if((fd = socket(AF_LOCAL,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		return -1;
	}
    struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	sun.sun_family = AF_LOCAL;
	strncpy(sun.sun_path,argv[1],strlen(argv[1]));
	if(connect(fd,(struct sockaddr *)&sun,sizeof(sun)) < 0)
	{
		perror("connect");
		return -1;
	}
	printf("client starung ... OK!\n");
	write(fd,"weiqing\n",strlen("weiqing\n"));
	return 0;
}
