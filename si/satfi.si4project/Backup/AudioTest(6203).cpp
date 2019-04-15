
#include <utils/Log.h>
#include <media/AudioRecord.h>
#include <stdio.h>
#include <stdlib.h>
#include <media/AudioTrack.h>
#include <binder/MemoryDealer.h>
#include <binder/MemoryHeapBase.h>
#include <binder/MemoryBase.h>
#include <binder/ProcessState.h>
#include <cutils/properties.h>
#include <media/AudioSystem.h>
#include <media/AudioTrack.h>

using namespace android;

#define LOG_TAG "AudioRecordTest"

int audio_test(void)
{
	//AudioRecordThread(strtol(argv[1], NULL, 0), strtol(argv[2], NULL, 0), argv[3]);
	size_t  minFrameCount1 	= 0;
	size_t  minFrameCount2 	= 0;
	size_t  minFrameCount 	= 0;
	int bufferSizeInBytes = 0;
	int framesize = 2;
	
	AudioTrack::getMinFrameCount(&minFrameCount1, AUDIO_STREAM_DEFAULT, 8000);
	
	AudioRecord::getMinFrameCount(&minFrameCount2, 8000, AUDIO_FORMAT_PCM_16_BIT, 1);
	
	sp<AudioTrack> track = new AudioTrack(AUDIO_STREAM_MUSIC, 8000, AUDIO_FORMAT_PCM_16_BIT, AUDIO_CHANNEL_OUT_MONO, 0);
	
	sp<AudioRecord> record = new AudioRecord(AUDIO_SOURCE_MIC, 8000, AUDIO_FORMAT_PCM_16_BIT, audio_channel_in_mask_from_count(1),
						String16(),(size_t)(framesize * minFrameCount), NULL, NULL, minFrameCount, AUDIO_SESSION_ALLOCATE,
						AudioRecord::TRANSFER_DEFAULT, AUDIO_INPUT_FLAG_NONE, -1, -1);
					
	minFrameCount = (minFrameCount1 > minFrameCount2) ? minFrameCount1 : minFrameCount2;	
						
	if(record->initCheck() != OK)
	{
		ALOGE("AudioRecord initCheck error!");
		return -1;
	}
	
	if(track->initCheck() != OK)
	{
		ALOGE("AudioTrack initCheck error!");
		track.clear();
		return -1;
	}	
	
	if(record->start()!= android::NO_ERROR)
	{
		ALOGE("AudioTrack start error!");
		record.clear();
		return -1;
	}
	
	if(track->start()!= android::NO_ERROR)
	{
		ALOGE("AudioTrack start error!");
		return -1;
	}
	
	bufferSizeInBytes = framesize * minFrameCount;
	void *inBuffer = malloc(bufferSizeInBytes);
	ALOGE("bufferSizeInBytes = %d", bufferSizeInBytes);
	
	while(1)
	{
		int readLen = record->read(inBuffer, bufferSizeInBytes);	
		//ALOGE("readLen = %d", readLen);
		track->write(inBuffer, readLen);
	}
	
	record->stop();
	track->stop();
	return 0;
}

