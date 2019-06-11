#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void Delayns(struct timespec* time_start, int time_ns)
{
	struct timespec time_end;
	int times_use;
	
	//usleep(time_ns/1000/4);
	
	while(1)
	{
		clock_gettime(CLOCK_REALTIME, &time_end);
		times_use = (time_end.tv_sec - time_start->tv_sec)*1000000000 + (time_end.tv_nsec - time_start->tv_nsec);
		if(times_use >= time_ns)
		{
			printf("times_use=%d\n", times_use);
			break;
		}
	}
}

int main(void)
{
	int cnt=100;
	
	struct timespec time_start;
	while(cnt>0)
	{
		clock_gettime(CLOCK_REALTIME, &time_start);
		Delayns(&time_start, 20000000);
		cnt--;
	}
	
	return 0;
}
