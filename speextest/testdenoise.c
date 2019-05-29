#include <stdint.h>
#include <speex/speex_echo.h>
#include <speex/speex_preprocess.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NN 160

#define OLD_FILE_PATH "record.pcm"
#define VOL_FILE_PATH "volnosie.pcm"


int main()
{
   short in[NN];
   int i;
   SpeexPreprocessState *st;
   int count=0;
   float f;

   st = speex_preprocess_state_init(NN, 8000);
   
   int noiseSuppress = -50;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_NOISE_SUPPRESS, &noiseSuppress);
   i=1;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DENOISE, &i);
   i=0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_AGC, &i);
   i=8000;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_AGC_LEVEL, &i);
   i=0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB, &i);
   f=.0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_DECAY, &f);
   f=.0;
   speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_DEREVERB_LEVEL, &f);
   
   FILE *fp = fopen(OLD_FILE_PATH, "rb+");
   FILE *fp_vol = fopen(VOL_FILE_PATH, "wb+");
   
   while (1)
   {
      int vad;
      fread(in, sizeof(short), NN, fp);
      if (feof(fp))
         break;
      vad = speex_preprocess_run(st, in);
      /*fprintf (stderr, "%d\n", vad);*/
      fwrite(in, sizeof(short), NN, fp_vol);
      count++;
   }
   speex_preprocess_state_destroy(st);
   return 0;
}
