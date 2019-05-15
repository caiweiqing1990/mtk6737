#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t playback_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t capture_mutex = PTHREAD_MUTEX_INITIALIZER;

int run = 0;

void *func_y(void *p)
{
	run = 1;
	while(1)
	{
		pthread_mutex_unlock(&capture_mutex);
		pthread_mutex_lock(&playback_mutex);
		printf("read\n");
		sleep(1);
	}
}

int main()
{
	pthread_t id_1;	
	pthread_mutex_lock(&playback_mutex);
	pthread_mutex_lock(&capture_mutex);
	
	if(pthread_create(&id_1, NULL, func_y, (void *)NULL) == -1) return -1;;
	
	while(1)
	{
		if(run == 1)
		{
			pthread_mutex_lock(&capture_mutex);
			pthread_mutex_unlock(&playback_mutex);
			printf("write\n");		
		}
		else
		{
			printf("run\n");
			sleep(1);
		}
	}
	
	return 0;
}