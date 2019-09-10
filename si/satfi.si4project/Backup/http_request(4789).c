#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define HTTP_DEFAULT_PORT 	80
#define BUFFER_SIZE 		2048
#define HTTP_GET 			"GET /%s HTTP/1.1\r\nHOST: %s:%d\r\nAccept: */*\r\n\r\n"

static int http_tcpclient_recv(int socket, char *lpbuff) {
    int ret = 0;
	int offset = 0;
	while(1)
	{
		ret = recv(socket, &lpbuff[offset], BUFFER_SIZE, 0);
		if(ret>0)
		{
			offset += ret;
		}
		
		if(ret<=0)
		{
			lpbuff[offset] = 0;
			//printf("%s", lpbuff);
			break;
		}
	}
    return offset;
}

static int http_tcpclient_create(const char *host, int port) {
    struct hostent *he;
    struct sockaddr_in server_addr; 
    int socket_fd;
 
    if((he = gethostbyname(host))==NULL){
        return -1;
    }
 
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);
   server_addr.sin_addr = *((struct in_addr *)he->h_addr);
 
    if((socket_fd = socket(AF_INET,SOCK_STREAM,0))==-1){
        return -1;
    }
 
    if(connect(socket_fd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
        return -1;
    }
 
    return socket_fd;
}
 
static void http_tcpclient_close(int socket) {
    close(socket);
}
 
static int http_parse_url(const char *url,char *host, char *data, int *port) {
	char *ptr1,*ptr2;
	int len = 0;
	if(!url || !host || !data || !port) {
		return -1;
	}

	ptr1 = (char *)url;
	if(!strncmp(ptr1, "http://", strlen("http://"))) {
		ptr1 += strlen("http://");
		} else {
		return -1;
	}

	ptr2 = strchr(ptr1,'/');
	if(ptr2) {
		len = strlen(ptr1) - strlen(ptr2);
		memcpy(host, ptr1, len);
		host[len] = '\0';
		if(*(ptr2 + 1)) {
			memcpy(data,ptr2 + 1, strlen(ptr2) - 1 );
			data[strlen(ptr2) - 1] = '\0';
		}
	} else {
		memcpy(host, ptr1, strlen(ptr1));
		host[strlen(ptr1)] = '\0';
	}
	//get host and ip
	ptr1 = strchr(host, ':');
	if(ptr1) {
		*ptr1++ = '\0';
		*port = atoi(ptr1);
	} else {
		*port = HTTP_DEFAULT_PORT;
	}

	return 0;
}

static int http_tcpclient_send(int socket, char *buff, int size) {
	int sent=0, tmpres=0;
	while(sent < size)
	{
		tmpres = send(socket, buff+sent, size-sent,0);
		if(tmpres == -1){
			return -1;
		}
		sent += tmpres;
	}
	return sent;
}

static char *http_parse_result(const char *buf) {
	char *ptmp = NULL; 
	char *response = NULL;
	
	ptmp = (char*)strstr(buf, "HTTP/1.1");
	if(!ptmp) {
	    printf("http/1.1 not faind\n");
	    return NULL;
	}
	
	if(atoi(ptmp + 9) != 200) {
	    printf("\n%s\n", buf);
	    return NULL;
	}

	ptmp = (char*)strstr(buf, "\r\n\r\n");
	if(!ptmp) {
	    //printf("ptmp is NULL\n");
	    return NULL;
	}
	
	response = (char *)malloc(strlen(ptmp)+1);
	if(!response) {
	    printf("malloc failed \n");
	    return NULL;
	}

	strcpy(response, ptmp+4);
	
	return response;
}

void http_result_free(char *response)
{
	if(response) {
		free(response);
	}
}

char *http_get(const char *url)
{
    int socket_fd = -1;
    char buf[BUFFER_SIZE] = {0};
    char *ptmp;
    char ip[64] = {0};
    char data[BUFFER_SIZE] = {0};
    int port = 0;
    int len=0;
 
    if(!url)
	{
        return NULL;
    }
 
    if(http_parse_url(url, ip, data, &port))
	{
        printf("http_parse_url failed!\n");
        return NULL;
    }
	
    //printf("%s:%d\n", ip, port);
	//printf("%s\n", data);
 
    socket_fd = http_tcpclient_create(ip, port);
    if(socket_fd < 0)
	{
        printf("http_tcpclient_create failed\n");
        return NULL;
    }
	
    sprintf(buf, HTTP_GET, data, ip, port);
    if(http_tcpclient_send(socket_fd, buf, strlen(buf)) < 0)
	{
        printf("http_tcpclient_send failed..\n");
        return NULL;
    }
 
    if(http_tcpclient_recv(socket_fd, buf) <= 0)
	{
        printf("http_tcpclient_recv failed\n");
        return NULL;
    }

	http_tcpclient_close(socket_fd);
 
	//printf("http recv data :\n\n%s\n\n", (char *)buf);
 
    return http_parse_result(buf);
}

//"http://192.168.88.1:10086/?op=login&guid=1234567890&host=112.35.28.14&port=6060&realm=4gpoc.com&impi=100310003&password=123456"
#define SERVER	"192.168.88.1"
#define PORT	10086
int login(char * guid, char *host, int port, char *realm, char *impi, char *password)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=login&guid=%s&host=%s&port=%d&realm=%s&impi=%s&password=%s", SERVER, PORT, guid, host, port, realm, impi, password);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
	return 0;
}

//http://192.168.88.1:10086/?op=logout&guid=1234567890
int logout(char * guid)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=logout&guid=%s", SERVER, PORT, guid);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
	return 0;
}

//http://127.0.0.1:10086/?op=requestTalk&guid=1234567890&sessionId=1
int requestTalk(char * guid, int sessionId)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=requestTalk&guid=%s&sessionId=%d", SERVER, PORT, guid, sessionId);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
}

//http://127.0.0.1:10086/?op=releaseTalk&guid=1234567890&sessionId=1
int releaseTalk(char * guid, int sessionId)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=releaseTalk&guid=%s&sessionId=%d", SERVER, PORT, guid, sessionId);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
}

//http://127.0.0.1:10086/?op=hangUp&guid=1234567890&sessionId=1
int hangUp(char * guid, int sessionId)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=hangUp&guid=%s&sessionId=%d", SERVER, PORT, guid, sessionId);
	printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
}

//http://127.0.0.1:10086/?op=acceptCall&guid=1234567890&sessionId=9
int acceptCall(char *guid, int sessionId)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=acceptCall&guid=%s&sessionId=%d", SERVER, PORT, guid, sessionId);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
}

//http://127.0.0.1:10086/?op=callOne&guid=1234567891&oneUri=sip:100310003@4gpoc.com
int callOne(char *guid, char *impi)
{
	char url[2048] = {0};
	sprintf(url, "http://%s:%d/?op=callOne&guid=%s&oneUri=sip:%s@4gpoc.com", SERVER, PORT, guid, impi);
	//printf("%s\n", url);
	char *result = http_get(url);
	if(result)
	{
		http_result_free(result);
	}
}
