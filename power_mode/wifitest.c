#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	static const char HOSTAPD_BIN_FILE[]    = "/system/bin/hostapd";
	static const char WIFI_ENTROPY_FILE[] = "/data/misc/wifi/entropy.bin";
	static const char HOSTAPD_CONF_FILE[] = "/data/misc/wifi/hostapd.conf";
	if(execl(HOSTAPD_BIN_FILE, HOSTAPD_BIN_FILE,"-e", WIFI_ENTROPY_FILE, HOSTAPD_CONF_FILE, (char *) NULL))
		printf("error\n");
	else
		printf("success\n");
	
}

