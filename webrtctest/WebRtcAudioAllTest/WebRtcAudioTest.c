// WebRtcAudioTest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "webrtc/modules/audio_processing/aec/include/echo_cancellation.h"
#include "webrtc/modules/audio_processing/agc/include/gain_control.h"
#include "webrtc/modules/audio_processing/ns/include/noise_suppression.h"
#include "webrtc/common_audio/signal_processing/include/signal_processing_library.h"

int WebRtcAecTest(int argc, char* argv[])
{
#define  NN 160
	short far_frame[NN];
	short near_frame[NN];
	short out_frame[NN];

	void *aecmInst = NULL;
	FILE *fp_far  = fopen("speaker.pcm", "rb");
	FILE *fp_near = fopen("micin.pcm", "rb");
	FILE *fp_out  = fopen("out.pcm", "wb");

	do 
	{
		if(!fp_far || !fp_near || !fp_out)
		{
			printf("WebRtcAecTest open file err \n");
			break;
		}

		WebRtcAec_Create(&aecmInst);
		WebRtcAec_Init(aecmInst, 8000, 8000);

		AecConfig config;
		config.nlpMode = kAecNlpConservative;
		WebRtcAec_set_config(aecmInst, config);

		while(1)
		{
			if (NN == fread(far_frame, sizeof(short), NN, fp_far))
			{
				fread(near_frame, sizeof(short), NN, fp_near);
				WebRtcAec_BufferFarend(aecmInst, far_frame, NN);//对参考声音(回声)的处理

				WebRtcAec_Process(aecmInst, near_frame, NULL, out_frame, NULL, NN, atoi(argv[1]),0);//回声消除
				fwrite(out_frame, sizeof(short), NN, fp_out);
			}
			else
			{
				break;
			}
		}
	} while (0);

	fclose(fp_far);
	fclose(fp_near);
	fclose(fp_out);
	WebRtcAec_Free(aecmInst);
	return 0;
}

int main(int argc, char* argv[])
{
	WebRtcAecTest(argc, argv);

	//WebRtcAgcTest("byby_8K_1C_16bit.pcm","byby_8K_1C_16bit_agc.pcm",8000);

	//WebRtcNS32KSample("lhydd_1C_16bit_32K.PCM","lhydd_1C_16bit_32K_ns.pcm",32000,1);

	//printf("声音增益，降噪结束...\n");

	//getchar();
	return 0;
}
