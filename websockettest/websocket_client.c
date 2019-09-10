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

void *httptest(void *p)
{
	char *username = (char *)p;
	char buf[1024] = {0};
	
	while(1)
	{
		printf("%s 1-login 2-acceptCall 3-requestTalk 4-releaseTalk 5-hangUp 6-logout : \n", username);
		printf("input username callone : ");
		fgets(buf, 1024, stdin);
		buf[strlen(buf) - 1] = 0;
		if(strlen(buf) == strlen(username))
		{
			callOne(username, buf);
		}		
		else if(buf[0] == '1')
		{
			login(username, "112.35.28.14", 6060, "4gpoc.com", username, "123456");
		}
		else if(buf[0] == '2')
		{
			if(fromsessionId > 0)
			{
				acceptCall(username, fromsessionId);
			}
			else if(tosessionId > 0)
			{
				acceptCall(username, tosessionId);
			}
		}
		else if(buf[0] == '3')
		{
			if(fromsessionId > 0)
			{
				requestTalk(username, fromsessionId);
			}
			else if(tosessionId > 0)
			{
				requestTalk(username, tosessionId);
			}
		}
		else if(buf[0] == '4')
		{
			if(fromsessionId > 0)
			{
				releaseTalk(username, fromsessionId);
			}
			else if(tosessionId > 0)
			{
				releaseTalk(username, tosessionId);
			}
		}
		else if(buf[0] == '5')
		{
			if(fromsessionId > 0)
			{
				hangUp(username, fromsessionId);
			}
			else if(tosessionId > 0)
			{
				hangUp(username, tosessionId);
			}
		}
		else if(buf[0] == '6')
		{
			logout(username, tosessionId);
		}
		else if(buf[0] == 'q')
		{
			exit(0);
		}
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
		printf("Usage: %s username\n", argv[1]);
		return -1;
	}
	
    fd = webSocket_clientLinkToServer("192.168.88.1", 10087, NULL);
    if(fd <= 0) {
        printf("webSocket_clientLinkToServer failed!\r\n");
        return -1;
    }

	char *username = argv[1];//用户名
    ret = webSocket_send(fd, username, strlen(username), true, WCT_TXTDATA);
	//base64_encode("sip:C1699&100310001@4gpoc.com", buf, strlen("sip:C1699&100310001@4gpoc.com"));
	if(pthread_create(&id_1, NULL, httptest, (void *)username) == -1) exit(1);
		
    while(1) {
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		timeout.tv_sec = 2;
		timeout.tv_usec = 0;
	    switch(select(fd+1, &fds, NULL, NULL, &timeout)) {
			case -1: break;
			case  0: break;
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
											printf("正在登陆");
										}
										
										if(jstmp->valueint == 102)
										{
											printf("登陆成功");
										}
										
										if(jstmp->valueint == 103)
										{
											printf("正在登出\n");
										}
										
										if(jstmp->valueint == 104)
										{
											printf("已经登出\n");
										}
										
										if(jstmp->valueint == 201)
										{
											printf("正在呼叫 ");
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
										}
									}
								}
								else if(jstmp->valueint == 2)
								{
									//"type":2
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp)
									{
										printf("tosessionId=%d ", jstmp->valueint);
										tosessionId = jstmp->valueint;
									}
									
									jstmp = cJSON_GetObjectItem(root, "fromWho");
									if(jstmp)
									{
										printf("fromWho=%s\n", jstmp->valuestring);
									}
								}
								else if(jstmp->valueint == 3)
								{
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp)
									{
										//printf("sessionId=%d ", jstmp->valueint);
									}
									
									jstmp = cJSON_GetObjectItem(root, "takenName");
									if(jstmp)
									{
										//printf("takenName=%s ", jstmp->valuestring);
									}
									
									jstmp = cJSON_GetObjectItem(root, "code");
									if(jstmp)
									{
										//printf("code=%d ", jstmp->valueint);
										if(jstmp->valueint == 301)
										{
											printf("被授权\n");
										}
										else if(jstmp->valueint == 302)
										{
											printf("别人正在讲话\n");
										}
										else if(jstmp->valueint == 303)
										{
											printf("用户已释放当前授权\n");
										}
										else if(jstmp->valueint == 304)
										{
											printf("用户处于空闲状态\n");
										}
										else if(jstmp->valueint == 305)
										{
											printf("用户讲话请求被拒绝\n");
										}
										else if(jstmp->valueint == 306)
										{
											printf("被剥夺说话权\n");
										}
										else if(jstmp->valueint == 307)
										{
											printf("收到一条命令\n");
										}
									}									
								}
								else
								{
									//printf("type=%d\n", jstmp->valueint);
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
