#include <stdio.h>
#include <stdint.h>
#include <speex/speex_preprocess.h>

#define NN 160

int main(int argc, char **argv)
{
	short in[NN];
	int i;
	SpeexPreprocessState *st;
	st = speex_preprocess_state_init(NN, 8000);

	int vad = 1;
	int vadProbStart = 90;
	int vadProbContinue = 100;
	speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_VAD, &vad);
	speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_PROB_START , &vadProbStart);
	speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_PROB_CONTINUE, &vadProbContinue);

	FILE *fp = fopen(argv[1], "rb+");
	FILE *fp_vol = fopen(argv[2], "wb+");
  
   while (1)
   {
      int vad;
      fread(in, sizeof(short), NN, fp);
      if (feof(fp))
         break;
      vad = speex_preprocess_run(st, in);
      /*fprintf (stderr, "%d\n", vad);*/
      if(vad)fwrite(in, sizeof(short), NN, fp_vol);
   }
   speex_preprocess_state_destroy(st);
   return 0;
}
