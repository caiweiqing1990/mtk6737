// Copyright 2008, The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
#define LOG_NDEBUG 0
#define LOG_TAG "shared_mem_test"

#include <stdlib.h>
#include <stdio.h>
#include <cutils/properties.h>
#include <media/AudioSystem.h>
#include <media/AudioTrack.h>
#include <math.h>

#include "shared_mem_test.h"
#include <binder/MemoryDealer.h>
#include <binder/MemoryHeapBase.h>
#include <binder/MemoryBase.h>
#include <binder/ProcessState.h>


#include <utils/Log.h>

#include <fcntl.h>

namespace android {

/************************************************************
*
*    Constructor
*
************************************************************/
AudioTrackTest::AudioTrackTest(void) {

    InitSine();         // init sine table

}


/************************************************************
*
*
************************************************************/
void AudioTrackTest::Execute(void) {
    if (Test01() == 0) {
        ALOGD("01 passed\n");
    } else {
        ALOGD("01 failed\n");
    }
}

/************************************************************
*
*    Shared memory test
*
************************************************************/
#define BUF_SZ 44100

int AudioTrackTest::Test01() {

	size_t  minFrameCount 	= 0;
	int bufferSizeInBytes;
	FILE *g_pAudioRecordFile = fopen("/mnt/1.pcm", "rb+");	

	AudioTrack::getMinFrameCount(&minFrameCount, AUDIO_STREAM_DEFAULT, 8000);
	
	//ALOGE("minFrameCount=%d",minFrameCount);
	
	bufferSizeInBytes = minFrameCount*2;
	void *inBuffer = malloc(bufferSizeInBytes);
	
	sp<AudioTrack> track = new AudioTrack(AUDIO_STREAM_MUSIC,// stream type
		   8000,
		   AUDIO_FORMAT_PCM_16_BIT,// word length, PCM
		   AUDIO_CHANNEL_OUT_MONO,
		   0);

	status_t status = track->initCheck();
	if(status != NO_ERROR) {
		track.clear();
		ALOGD("Failed for initCheck()");
		return -1;
	}

	// start play
	ALOGD("start");
	track->start();

	int n;
	while(1)
	{
		if((n = fread(inBuffer, 1, bufferSizeInBytes, g_pAudioRecordFile)) > 0)
		{
			ALOGD("write n=%d",n);
			track->write(inBuffer, bufferSizeInBytes);
		}
		else
		{
			track->stop();
			break;
		}
	}

    return 0;

}

/************************************************************
*
*    Generate a mono buffer
*    Error is less than 3lsb
*
************************************************************/
void AudioTrackTest::Generate(short *buffer, long bufferSz, long amplitude, unsigned long &phi, long dPhi)
{
    // fill buffer
    for(int i0=0; i0<bufferSz; i0++) {
        buffer[i0] = ComputeSine( amplitude, phi);
        phi += dPhi;
    }
}

/************************************************************
*
*    Generate a sine
*    Error is less than 3lsb
*
************************************************************/
short AudioTrackTest::ComputeSine(long amplitude, long phi)
{
    long pi13 = 25736;   // 2^13*pi
    long sample;
    long l0, l1;

    sample = (amplitude*sin1024[(phi>>22) & 0x3ff]) >> 15;
    // correct with interpolation
    l0 = (phi>>12) & 0x3ff;         // 2^20 * x / (2*pi)
    l1 = (amplitude*sin1024[((phi>>22) + 256) & 0x3ff]) >> 15;    // 2^15*cosine
    l0 = (l0 * l1) >> 10;
    l0 = (l0 * pi13) >> 22;
    sample = sample + l0;

    return (short)sample;
}


/************************************************************
*
*    init sine table
*
************************************************************/
void AudioTrackTest::InitSine(void) {
    double phi = 0;
    double dPhi = 2 * M_PI / SIN_SZ;
    for(int i0 = 0; i0<SIN_SZ; i0++) {
        long d0;

        d0 = 32768. * sin(phi);
        phi += dPhi;
        if(d0 >= 32767) d0 = 32767;
        if(d0 <= -32768) d0 = -32768;
        sin1024[i0] = (short)d0;
    }
}

/************************************************************
*
*    main in name space
*
************************************************************/
int main() {
    ProcessState::self()->startThreadPool();
    AudioTrackTest *test;

    test = new AudioTrackTest();
    test->Execute();
    delete test;

    return 0;
}

}

/************************************************************
*
*    global main
*
************************************************************/
int main() {

    return android::main();
}
