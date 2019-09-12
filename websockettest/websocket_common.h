#ifndef _WEBSOCKET_COMMON_H_
#define _WEBSOCKET_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// websocket根据data[0]判别数据包类型    比如0x81 = 0x80 | 0x1 为一个txt类型数据包
typedef enum {
    WCT_MINDATA = -20,      // 0x0：标识一个中间数据包
    WCT_TXTDATA = -19,      // 0x1：标识一个txt类型数据包
    WCT_BINDATA = -18,      // 0x2：标识一个bin类型数据包
    WCT_DISCONN = -17,      // 0x8：标识一个断开连接类型数据包
    WCT_PING = -16,     // 0x8：标识一个断开连接类型数据包
    WCT_PONG = -15,     // 0xA：表示一个pong类型数据包
    WCT_ERR = -1,
    WCT_NULL = 0
}Websocket_CommunicationType;

//编码
extern int base64_encode( const unsigned char *bindata, char *base64, int binlength);
//解码
extern int base64_decode( const char *base64, unsigned char *bindata);

extern void http_result_free(char *response);
extern char *http_get(const char *url);

extern int callOne(char *from, char *to);
extern int acceptCall(char *guid, int sessionId);
extern int hangUp(char * guid, int sessionId);
extern int releaseTalk(char * guid, int sessionId);
extern int requestTalk(char * guid, int sessionId);
extern int logout(char * guid);
extern int login(char * guid, char *host, int port, char *realm, char *impi, char *password);
// server回复client的http请求
//int webSocket_serverLinkToClient(int fd, char *recvBuf, unsigned int bufLen);
// client向server发送http连接请求, 并处理返回
extern int webSocket_clientLinkToServer(char *ip, int port, char *interface_path);
extern int webSocket_send(int fd, unsigned char *data, unsigned int dataLen, bool mod, Websocket_CommunicationType type);
extern int webSocket_recv(int fd, unsigned char *data, unsigned int dataMaxLen);
#endif
