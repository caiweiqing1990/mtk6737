#include <sys/select.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include <pthread.h>
#include "websocket_common.h"
#include "cJSON.h"

char *username = NULL;
int SessionID = 0;
int fromWhoSessionID = 0;

void *httptest(void *p)
{
	char buf[1024] = {0};
	int Sid = 0;
	
	while(1)
	{
		printf("%s 1-login 2-logout 3-callOne 4-acceptCall 5-requestTalk 6-releaseTalk 7-hangUp q-exit: ", username);
		fgets(buf, 1024, stdin);
		buf[strlen(buf) - 1] = 0;
		
		if(fromWhoSessionID > 0) {
			Sid = fromWhoSessionID;
		}	
		else if(SessionID > 0) {
			Sid = SessionID;
		}
		
		if(buf[0] == '1')
		{
			login(username, "112.35.28.14", 6060, "4gpoc.com", username, "123456");
		}
		else if(buf[0] == '2')
		{
			logout(username);
		}
		else if(buf[0] == '3')
		{
			static char name[24] = {0};
			printf("input username to call: %s", name);
			fgets(buf, 1024, stdin);
			buf[strlen(buf) - 1] = 0;
			if(strlen(username) == strlen(buf) && strcmp(username, buf) != 0)
			{
				strcpy(name, buf);
				callOne(username, name);
			}
			else if(strlen(username) == strlen(name))
			{
				callOne(username, name);
			}			
		}
		else if(buf[0] == '4')
		{
			if(Sid > 0)
			{
				acceptCall(username, Sid);
			}
		}
		else if(buf[0] == '5')
		{
			if(Sid > 0)
			{
				requestTalk(username, Sid);
			}
		}
		else if(buf[0] == '6')
		{
			if(Sid > 0)
			{
				releaseTalk(username, Sid);
			}
		}
		else if(buf[0] == '7')
		{
			if(Sid > 0)
			{
				hangUp(username, Sid);
			}
		}
		else if(buf[0] == 'q')
		{
			exit(0);
		}
	}
	
	return NULL;
}

//websocket_client 100310003 100310004
int main(int argc, char *argv[])
{
    int ret;
    int fd = -1;
	fd_set fds;
    char buf[1024] = {0};
	struct timeval timeout = {3,0};

	pthread_t id_1;
	cJSON *root,*jstmp;	
	
	if(argc != 2) {
		printf("Usage: %s username\n", argv[0]);
		return -1;
	}
	
	username = argv[1];//用户名
	//base64_encode("sip:C1699&100310001@4gpoc.com", buf, strlen("sip:C1699&100310001@4gpoc.com"));
	if(pthread_create(&id_1, NULL, httptest, (void *)NULL) == -1) exit(1);

    while(1) {
		if(fd <= 0) {
			fd = webSocket_clientLinkToServer("192.168.88.1", 10087, NULL);
			if(fd <= 0) {
				printf("\nwebSocket_clientLinkToServer failed!\r\n");
				sleep(5);
				continue;
			} else {
				printf("\nwebSocket_clientLinkToServer success!\r\n");
				SessionID=0; fromWhoSessionID=0;
				webSocket_send(fd, username, strlen(username), true, WCT_TXTDATA);
			}
		}
		
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
						if(root) {
							jstmp = cJSON_GetObjectItem(root, "type");
							if(jstmp) {
								//printf("type=%d\n", jstmp->valueint);
								if(jstmp->valueint == 1) {
									//"type":1
									jstmp = cJSON_GetObjectItem(root, "code");
									if(jstmp) {
										//printf("code=%d\n", jstmp->valueint);
										if(jstmp->valueint == 101) {
											printf("\n正在登陆\n");
										}
										
										if(jstmp->valueint == 102) {
											printf("\n登陆成功\n");
										}
										
										if(jstmp->valueint == 103) {
											printf("\n正在登出\n");
										}
										
										if(jstmp->valueint == 104) {
											printf("\n已经登出\n");
										}
										
										if(jstmp->valueint == 201) {
											printf("\n正在呼叫 ");
											jstmp = cJSON_GetObjectItem(root, "sessionId");
											if(jstmp) {
												if(fromWhoSessionID == 0 && SessionID == 0) {
													SessionID = jstmp->valueint;
												}
												printf("SessionID=%d\n", SessionID);
											}
										}
										
										if(jstmp->valueint == 202) {
											printf("\n呼叫成功\n");
										}
										
										if(jstmp->valueint == 203) {
											printf("\n正在挂断\n");
										}
										
										if(jstmp->valueint == 204) {
											printf("\n呼叫终止\n");
											SessionID=0; fromWhoSessionID=0;
										}
									}
								}
								else if(jstmp->valueint == 2) {
									//"type":2
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp) {
										printf("\nfromWhoSessionID=%d ", jstmp->valueint);
										fromWhoSessionID = jstmp->valueint;
									}
									
									jstmp = cJSON_GetObjectItem(root, "fromWho");
									if(jstmp) {
										printf("fromWho=%s\n", jstmp->valuestring);
									}
								}
								else if(jstmp->valueint == 3) {
									jstmp = cJSON_GetObjectItem(root, "sessionId");
									if(jstmp) {
										//printf("sessionId=%d ", jstmp->valueint);
									}
									
									jstmp = cJSON_GetObjectItem(root, "takenName");
									if(jstmp) {
										//printf("takenName=%s ", jstmp->valuestring);
									}
									
									jstmp = cJSON_GetObjectItem(root, "code");
									if(jstmp) {
										//printf("code=%d ", jstmp->valueint);
										if(jstmp->valueint == 301)
										{
											printf("\n被授权\n");
										} else if(jstmp->valueint == 302) {
											printf("\n别人正在讲话\n");
										} else if(jstmp->valueint == 303) {
											printf("\n用户已释放当前授权\n");
										} else if(jstmp->valueint == 304) {
											printf("\n用户处于空闲状态\n");
										} else if(jstmp->valueint == 305) {
											printf("\n用户讲话请求被拒绝\n");
										} else if(jstmp->valueint == 306) {
											printf("\n被剥夺说话权\n");
										} else if(jstmp->valueint == 307) {
											printf("\n收到一条命令\n");
										}
									}						
								} else {
									//printf("type=%d\n", jstmp->valueint);
								}
							}

							cJSON_Delete(root);
						} else {
							printf("cJSON_Parse error\n");
							printf("%s\r\n", buf);
						}
					} else {
						perror("webSocket_recv");
						if(errno == EAGAIN || errno == EINTR) {
							continue;
						} else {
							close(fd);
							fd = -1;
						}
					}
				}
				break;
			}
		}
    }

    return 0;
}
