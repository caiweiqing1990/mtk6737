#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int modem_update(char *ttyName, char *fileName);

#define SERIAL_PORT		"/dev/ttyMT1"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s update_file\n", argv[0]);
		return -1;
	}
	printf("modem_update\n");
	modem_update(SERIAL_PORT, argv[1]);
	printf("modem_update success\n");
	return 0;
}

