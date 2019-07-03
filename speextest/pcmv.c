#include <stdio.h>

#define OLD_FILE_PATH "record.pcm"
#define VOL_FILE_PATH "vol.pcm"
 
int volume_adjust(short  * in_buf, float in_vol, int len)
{
	int i, tmp;
	for(i=0; i<len; i+=2)
	{
		tmp = (*in_buf)*in_vol;
		if(tmp > 32767)
		{
			tmp = 32767;
		}
		else if(tmp < -32768)
		{
			tmp = -32768;
		}
		*in_buf = tmp;
		++in_buf;
	}
	return len;
}
 
void pcm_volume_control(char* file1, char* file2, float volume)
{
    short s16In[160];
    short s16Out[160];
    int size = 0;
 
    FILE *fp = fopen(file1, "rb+");
    FILE *fp_vol = fopen(file2, "wb+");
 
    while(!feof(fp))
    {
        size = fread(s16In, 1, 320, fp);
        if(size>0)
        {        
            volume_adjust(s16In, volume, size);
            fwrite(s16In, 1, 320, fp_vol);       
        }
    }
 
    fclose(fp);
    fclose(fp_vol);
}
 
int main(int argc, char **argv)
{
	float volumeFactor;	
	short Volume = 2;
	printf("vol=%f\n", (Volume)*1.0 / 10);
    pcm_volume_control(argv[1], argv[2], 8); 
    return 0;
}