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

#define UNIX_DOMAIN_FILE "/tmp/my_domain_file"

int LocalSocketCreate(const char *path)
{
	int fd;
	if((fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
	{
		printf("LocalSocketCreate error");
		exit(-1);
	}
	
	//int reuse = 1;
	//setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)); 
	
    struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	sun.sun_family = AF_LOCAL;

	unlink(path);
	strncpy(sun.sun_path, path, strlen(path));

	if(bind(fd, (struct sockaddr *)&sun, sizeof(sun)))
	{
		printf("LocalSocketCreate bind error");
		exit(-1);
	}

	if(listen(fd, 5) < 0)
	{
		printf("LocalSocketCreate listen error");
		exit(-1);
	}
	
	return fd;
}

void *local_socket_server(void *p)
{	
	struct timeval timeout;
	int ret = -1;
	int max_fd = -1;
	fd_set fds;
	fd_set fdread;
	struct sockaddr_in cli_addr;  
	int len = sizeof(struct sockaddr_in);
	int clientfd = -1;
	char buf[2048] = {0};
	int LocalSocketfd = LocalSocketCreate("socket_audio_cancel");

	printf("LocalSocketCreate=%d\n", LocalSocketfd); 
	FD_ZERO(&fds);
	FD_ZERO(&fdread);

	FD_SET(LocalSocketfd, &fdread);

	max_fd = LocalSocketfd;
	
	while(1)
	{
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		fds = fdread;
		ret = select(max_fd + 1, &fds, NULL, NULL, &timeout);		
        if (ret == 0)
        {
            //satfi_log("app select timeout %d %d\n", web_socket_listen, sock_app_tcp);  
        }
        else if (ret < 0)
        {  
            printf("LocalSocketCreate error occur\n"); 
			sleep(1);
        }
		else
		{
			if(FD_ISSET(LocalSocketfd, &fds))
			{
				if(clientfd > 0)
				{
					FD_CLR(clientfd, &fdread);
					close(clientfd);
					max_fd = LocalSocketfd;
				}
			
				clientfd = accept(LocalSocketfd, (struct sockaddr*)&cli_addr, &len);
				printf("LocalSocketfd comes %d\n", clientfd);
				if(clientfd > 0)
				{
					FD_SET(clientfd, &fdread);
					if(clientfd > max_fd)
					{
						max_fd = clientfd;
					}
				}
				else
				{
					printf("LocalSocketfd Fail to accept\n");
					exit(0);
				}
			}

			if(clientfd > 0)
			{
				if(FD_ISSET(clientfd, &fds))
				{
					int n = read(clientfd, buf, 2048);
					if(n>0)
					{
						buf[n] = 0;
						printf("LocalSocket:%s", buf);
					}
					else
					{
						printf("close(LocalSocketfd)\n");
						FD_CLR(clientfd, &fdread);
						close(clientfd);
						clientfd = -1;
						max_fd = LocalSocketfd;
					}
				}
			}
		}
	}

	return NULL;
}

int main(int argc, const char *argv[])
{
	int fd;
	if((fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(-1);
	}
	
	//int reuse = 1;
	//setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)); 
	
    struct sockaddr_un sun;
	bzero(&sun,sizeof(sun));
	sun.sun_family = AF_LOCAL;

	unlink(UNIX_DOMAIN_FILE);
	strncpy(sun.sun_path, UNIX_DOMAIN_FILE, strlen(UNIX_DOMAIN_FILE));

	if(bind(fd, (struct sockaddr *)&sun, sizeof(sun)))
	{
		perror("bind");
		exit(-1);
	}

	if(listen(fd, 5) < 0)
	{
		perror("listen");
		exit(-1);
	}
	
	//local_socket_server(NULL);
	
	return 0;
}
