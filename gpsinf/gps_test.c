#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>
#include "mtk_lbs_utility.h"
#include "data_coder.h"

#define HAL_MNL_BUFF_SIZE           (16 * 1024)
#define HAL_MNL_INTERFACE_VERSION   1

#define MTK_HAL2MNL "mtk_hal2mnl"

typedef enum {
    HAL2MNL_HAL_REBOOT                      = 0,
    HAL2MNL_GPS_INIT                        = 101,
    HAL2MNL_GPS_START                       = 102,
    HAL2MNL_GPS_STOP                        = 103,
    HAL2MNL_GPS_CLEANUP                     = 104,
    HAL2MNL_GPS_INJECT_TIME                 = 105,
    HAL2MNL_GPS_INJECT_LOCATION             = 106,
    HAL2MNL_GPS_DELETE_AIDING_DATA          = 107,
    HAL2MNL_GPS_SET_POSITION_MODE           = 108,
    HAL2MNL_DATA_CONN_OPEN                  = 201,
    HAL2MNL_DATA_CONN_OPEN_WITH_APN_IP_TYPE = 202,
    HAL2MNL_DATA_CONN_CLOSED                = 203,
    HAL2MNL_DATA_CONN_FAILED                = 204,
    HAL2MNL_SET_SERVER                      = 301,
    HAL2MNL_SET_REF_LOCATION                = 302,
    HAL2MNL_SET_ID                          = 303,
    HAL2MNL_NI_MESSAGE                      = 401,
    HAL2MNL_NI_RESPOND                      = 402,
    HAL2MNL_UPDATE_NETWORK_STATE            = 501,
    HAL2MNL_UPDATE_NETWORK_AVAILABILITY     = 502,
    HAL2MNL_GPS_MEASUREMENT                 = 601,
    HAL2MNL_GPS_NAVIGATION                  = 602,
} hal2mnl_cmd;

int gps_start() {
    printf("gps_start\n");
    char buff[HAL_MNL_BUFF_SIZE] = {0};
    int offset = 0;
    put_int(buff, &offset, HAL_MNL_INTERFACE_VERSION);
    put_int(buff, &offset, HAL2MNL_GPS_START);
    return safe_sendto(MTK_HAL2MNL, buff, offset);
}

int gps_stop() {
    printf("gps_stop\n");
    char buff[HAL_MNL_BUFF_SIZE] = {0};
    int offset = 0;
    put_int(buff, &offset, HAL_MNL_INTERFACE_VERSION);
    put_int(buff, &offset, HAL2MNL_GPS_STOP);
    return safe_sendto(MTK_HAL2MNL, buff, offset);
}

//一、处理消息进程日志
//logcat | grep MNLD

//二、发送消息接口日志
//logcat | grep hal2mnl

//三、抓取定位数据日志
//logcat | grep pseudo

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("%s <start|stop>\n", argv[0]);
		return -1;
	}
	
	if(strcmp(argv[1], "start") == 0)
	{
		gps_start();
	} 
	else if(strcmp(argv[1], "stop") == 0)
	{
		gps_stop();
	}
	else
	{
		printf("%s <start|stop>\n", argv[0]);
		return -1;
	}
	
	return 0;
}

