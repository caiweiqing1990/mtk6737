/*Ä£¿éÉý¼¶²âÊÔ³ÌÐò*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <utils/Log.h>

extern int modem_update(const char * devpath, const char * path);

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("eg: %s /dev/ttyMT1 /mnt/tt_update.bin\n", argv[0]);
		return -1;
	}
	
	int ret;
	printf("%s %s\n", argv[1], argv[2]);
	ret = modem_update(argv[1], argv[2]);
	RLOGI("tt modem update ret = %d\n", ret);
	printf("tt modem update ret = %d\n", ret);
	return 0;
}
