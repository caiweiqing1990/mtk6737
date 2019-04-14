#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include "websocket.h"

int main()
{
#define REQUEST_LEN_MAX         1024
#define DEFEULT_SERVER_PORT     8000
    int listen_fd;
    int conn_fd;
    char buf[REQUEST_LEN_MAX];
    char *data = NULL;
    char str[INET_ADDRSTRLEN];
    char *sec_websocket_key = NULL;
    int n;
    int connected = 0;
    int port = DEFEULT_SERVER_PORT;
    struct sockaddr_in  servaddr;
    struct sockaddr_in  cliaddr;
    socklen_t addr_len;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
	{
		printf("bind error\n");
		exit(0);
	}
	
    listen(listen_fd, 5);
    printf("Listen %d\nAccepting connections ...\n",port);
    addr_len = sizeof(struct sockaddr_in);
 
    while (1)
    {
		conn_fd = accept(listen_fd, (struct sockaddr *)&cliaddr, &addr_len);
		printf("From %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
        
		while(1)
		{
			memset(buf, 0, REQUEST_LEN_MAX);
			n = read(conn_fd, buf, REQUEST_LEN_MAX);	
			printf("--------------------- %d\n", n);	 
			if(!connected) 
			{
				printf("read:%d\n%s\n", n, buf);
				sec_websocket_key = calculate_accept_key(buf);	
				websocket_shakehand(conn_fd, sec_websocket_key);
				if (sec_websocket_key != NULL)
				{
					free(sec_websocket_key);
					sec_websocket_key = NULL;
				}
				connected=1;
				continue;
			}
						
			data = deal_data(buf, &n);
			if(data)
			{
				data[n] = 0;
				response(conn_fd, data);
			}
			
			if(n <= 0)
			{
				printf("close(conn_fd)\n");
				connected = 0;
				close(conn_fd);
				break;
			}			
		}
    }
 
    close(conn_fd);
    return 0;
}