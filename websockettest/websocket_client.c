#include <sys/select.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include <pthread.h>
#include "websocket_common.h"
#include "cJSON.h"

//单呼
int fromsessionId = 0;
int tosessionId = 0;

int ilogin = 0;
int sessionId = 0;

int stop = 0;

void *httptest(void *p)
{
	char *username = (char *)p;
	
	while(1)
	{
		if(ilogin == 0)
		{
			login(username, "112.35.28.14", 6060, "4gpoc.com", username, "123456");
		}
		
		if(sessionId > 0)
		{
			printf("接听来电\n");
			acceptCall(username, sessionId);
			sessionId = 0;
		}
		
		if(stop > 0)
		{
			if(fromsessionId > 0)
			{
				hangUp(username, fromsessionId);
				fromsessionId = 0;
			}

			if(tosessionId > 0)
			{
				hangUp(username, tosessionId);
				tosessionId = 0;
			}
						
			logout(username);
			
			stop = 0;
		}
		
		sleep(1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
    int ret;
    int fd;
	fd_set fds;
    char buf[1024] = {0};
	struct timeval timeout = {3,0};

	pthread_t id_1;
	cJSON *root,*jstmp;

	if(argc != 2)
	{
		printf("%s username\n", argv[0]);
		return -1;
	}	
	
    fd = webSocket_clientLinkToServer("192.168.88.1", 10087, NULL);
    if(fd <= 0) {
        printf("webSocket_clientLinkToServer failed!\r\n");
        return -1;
    }

	char *username = argv[1];	//用户名		
    ret = webSocket_send(fd, username, strlen(username), true, WCT_TXTDATA);
	//base64_encode("sip:C1699&100310001@4gpoc.com", buf, strlen("sip:C1699&100310001@4gpoc.com"));
	if(pthread_create(&id_1, NULL, httptest, (void *)username) == -1) exit(1);
	
    while(1) {
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
	    switch(select(fd+1, &fds, NULL, NULL, &timeout)) {
			case -1: break;
			case  0: {
				if(fromsessionId > 0 || 0 < tosessionId) stop = 1;
			}
			default: {
				if(FD_ISSET(fd, &fds)) {
					memset(buf, 0, sizeof(buf));
					ret = webSocket_recv(fd, buf, sizeof(buf));
					if(ret > 0) {
						//printf("%s\n", buf);
						root = cJSON_Parse(buf);
						if(root)
						{
							jstmp = cJSON_GetObjectItem(root, "type");
							if(jstmp)
							{
								//printf("type=%d\n", jstmp->valueint);
								if(jstmp->valueint == 1)
								{
									//"type":1
									jstmp = cJSON_GetObjectItem(root, "code");
									if(jstmp)
									{
										//printf("code=%d\n", jstmp->valueint);
										if(jstmp->valueint == 101)
										{
											printf("正在登陆\n");
										}
										
										if(jstmp->valueint == 102)
										{
											printf("登陆成功\n");
											ilogin = 1;
										}
										
										if(jstmp->valueint == 103)
										{
											printf("正在登出\n");
										}
										
										if(jstmp->valueint == 104)
										{
											printf("已经登出\n");
											ilogin = 0;
										}
										
										if(jstmp->valueint == 201)
										{
											printf("正在呼叫\n");
											jstmp = cJSON_GetObjectItem(root, "sessionId");
											if(jstmp)
											{
												if(tosessionId == 0 && fromsessionId == 0)
												{
													fromsessionId = jstmp->valueint;
													printf("fromsessionId=%d\n", fromsessionId);
												}
											}
										}
										
										if(jstmp->valueint == 202)
										{
											printf("呼叫成功\n");
										}
										
										if(jstmp->valueint == 203)
										{
											printf("正在挂断\n");
										}
										
										if(jstmp->valueint == 204)
										{
											printf("呼叫终止\n");
											sessionId = 0;
										}
									}
								}
								else if(jstmp->valueint == 2)
								{
									//"type":2
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp)
									{
										printf("tosessionId=%d\n", jstmp->valueint);
										sessionId = jstmp->valueint;
										tosessionId = sessionId;
									}
									
									jstmp = cJSON_GetObjectItem(root, "fromWho");
									if(jstmp)
									{
										printf("fromWho=%s\n", jstmp->valuestring);
									}
								}
								else
								{
									//printf("%s\r\n", buf);
								}
							}

							cJSON_Delete(root);
						}
						else
						{
							printf("cJSON_Parse error\n");
							printf("%s\r\n", buf);
						}
					}
					else {
						perror("webSocket_recv");
						if(errno == EAGAIN || errno == EINTR) {
							continue;
						}
						else {
							close(fd);
							return 0;
						}
					}
				}
				break;
			}
		}
    }

    return 0;
}
