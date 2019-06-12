#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
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


int myexec(const char *command, char *result, int *maxline)
{
  FILE *pp = popen(command, "r");
  if(NULL == pp) return -1;
  //satfi_log("execute shell : %s\n", command);
  char tmp[1024];
  if(result!=NULL)
  {
    int line=0;
    while(fgets(tmp,sizeof(tmp),pp)!=NULL)
    {
      if('\n' == tmp[strlen(tmp)-1]) tmp[strlen(tmp)-1] = '\0';
      if(maxline!=NULL && line++<*maxline) strcat(result,tmp);
      printf("tmp=%s\n", tmp);
    }
    *maxline = line;
  }
  
  int rc = pclose(pp);
  return rc;
}

int main()
{
	int maxline = 1;
	int n = 0;
	char buf[2048] = {0};
	myexec("rm update.zip", NULL, NULL);
	myexec("busybox wget -c http://zzhjjt.tt-box.cn:9098/TSCWEB/satfi/update.zip -O update.zip > file.tmp 2>&1 &", buf, &maxline);
	
	int sizeold=0;
	int size=0;
	
	while(1)
	{
		sleep(1);
		
		int fd = open("file.tmp", O_RDONLY);
		if(fd > 0)
		{
			size = lseek(fd,0,SEEK_END);			
			if(size != sizeold)
			{
				bzero(buf, sizeof(buf));
				lseek(fd, sizeold, SEEK_SET);
				n = read(fd, buf, sizeof(buf));
				//printf("%d %d %d\n", size, sizeold, n);	
				char *p = strchr(buf, '%');
				if(p != NULL)
				{
					buf[p - buf] = 0;
					//printf("%s\n", buf);
					p = strrchr(buf, ' ');
					//printf("%s\n", p+1);
					int percent = atoi(p+1);
					printf("%d\n", percent);
				}
			}
			close(fd);
			sizeold = size;
		}
	}
	
	return 0;
}
