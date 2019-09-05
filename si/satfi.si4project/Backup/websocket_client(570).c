#include "websocket_common.h"
 
char ip[] = "192.168.88.1";//"192.168.244.128";   // 服务器IP
int port = 10087;        // 服务器端口
 
int main(void)
{
    int ret, timeCount = 0;
    int fd;
    char buf[1024];
    //
    fd = webSocket_clientLinkToServer(ip, port, "/null");
    if(fd <= 0)
    {
        printf("client link to server failed !\r\n");
        return -1;
    }
    //
    sleep(1);
	
	char *op = "op=login&guid=1234567890&host=112.35.28.14&port=6060&realm=4gpoc.com&impi=100310003&password=123456";
	
    //
    ret = webSocket_send(fd, op, strlen(op), true, WCT_TXTDATA);
    //
    printf("\r\n\r\n========== client start ! ==========\r\n\r\n");
    //
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        ret = webSocket_recv(fd, buf, sizeof(buf));
        if(ret > 0)
        {
            printf("client recv : %s\r\n", buf);
            if(ret <= 0)    // send返回负数, 连接已断开
            {
                close(fd);
                break;
            }
        }
        else    // 检查错误, 是否连接已断开
        {
            if(errno == EAGAIN || errno == EINTR)
                ;
            else
            {
                close(fd);
                break;
            }
        }
        //
        usleep(500000);

    }
    printf("client close !\r\n");
    return 0;
}
