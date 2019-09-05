#include <sys/select.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include "websocket_common.h"
#include "cJSON.h"

char ip[] = "192.168.88.1";//"192.168.244.128";   // 服务器IP
int port = 10087;        // 服务器端口
 
int main(int argc, char *argv[])
{
    int ret;
    int fd;
	fd_set fds;
    char buf[1024] = {0};
	struct timeval timeout = {3,0};

	cJSON *root,*jstmp;
	
    fd = webSocket_clientLinkToServer(argv[1], port, NULL);
    if(fd <= 0) {
        printf("webSocket_clientLinkToServer failed !\r\n");
        return -1;
    }

	//char *op = "op=login&guid=1234567890&host=112.35.28.14&port=6060&realm=4gpoc.com&impi=100310003&password=123456";
	char *op = argv[2];
    ret = webSocket_send(fd, op, strlen(op), true, WCT_TXTDATA);

	//base64_encode("sip:C1699&100310001@4gpoc.com", buf, strlen("sip:C1699&100310001@4gpoc.com"));
	//printf("%s\n", buf);

    while(1) {
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
	    switch(select(fd+1, &fds, NULL, NULL, &timeout)) {
			case -1: break;
			case  0: break;
			default: {
				if(FD_ISSET(fd, &fds)) {
					memset(buf, 0, sizeof(buf));
					ret = webSocket_recv(fd, buf, sizeof(buf));
					if(ret > 0) {
						printf("%s\r\n", buf);
						root = cJSON_Parse(buf);
						if(root)
						{
							jstmp = cJSON_GetObjectItem(root, "type");
							if(jstmp)
							{
								//printf("type=%d\n", jstmp->valueint);
								if(jstmp->valueint == 1)
								{
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp)
									{
										//printf("sessionId=%d\n", jstmp->valueint);
									}
									
									jstmp = cJSON_GetObjectItem(root, "code");
									if(jstmp)
									{
										//printf("code=%d\n", jstmp->valueint);
									}
								}
							}

							cJSON_Delete(root);
						}
						else
						{
							printf("cJSON_Parse error\n");
						}
					}
					else {
						perror("webSocket_recv");
						if(errno == EAGAIN || errno == EINTR) {
							continue;
						}
						else {
							close(fd);
							break;
						}
					}
				}
				break;
			}
		}
    }

    return 0;
}
