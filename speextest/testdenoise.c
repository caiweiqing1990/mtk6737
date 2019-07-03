#include <stdio.h>
#include <stdint.h>
#include <speex/speex_preprocess.h>

#define NN 160

int main(int argc, char **argv)
{
	short in[NN];
	
	SpeexPreprocessState *st;
	float f;
	int i;
	st = speex_preprocess_state_init(NN, 8000);
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

	int vad = 1;
	int vadProbStart = 90;
	int vadProbContinue = 100;
	SpeexPreprocessState *st1;
	st1 = speex_preprocess_state_init(NN, 8000);
	speex_preprocess_ctl(st1, SPEEX_PREPROCESS_SET_VAD, &vad);
	speex_preprocess_ctl(st1, SPEEX_PREPROCESS_SET_PROB_START , &vadProbStart);
	speex_preprocess_ctl(st1, SPEEX_PREPROCESS_SET_PROB_CONTINUE, &vadProbContinue);

	FILE *fp = fopen(argv[1], "rb+");
	FILE *fp_vol = fopen(argv[2], "wb+");
  
   
   while (1)
   {
		fread(in, sizeof(short), NN, fp);
		if (feof(fp))
			break;
		speex_preprocess_run(st, in);
		vad = speex_preprocess_run(st1, in);
		/*fprintf (stderr, "%d\n", vad);*/
		fwrite(in, sizeof(short), NN, fp_vol);
   }
   speex_preprocess_state_destroy(st);
   return 0;
}
