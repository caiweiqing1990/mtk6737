
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace android;

#define LOG_TAG "AudioRecordTest"

static void *AudioRecordThread(int sample_rate, int channels, void *fileName)
{
	void *inBuffer = NULL; 
	audio_source_t inputSource = AUDIO_SOURCE_MIC;
	audio_format_t 	audioFormat = AUDIO_FORMAT_PCM_16_BIT;	
	audio_channel_mask_t channelConfig = AUDIO_CHANNEL_IN_MONO;
	int bufferSizeInBytes;
	int sampleRateInHz = sample_rate; //8000; //44100;	
	AudioRecord *pAudioRecord = NULL;
	FILE *g_pAudioRecordFile = NULL;
	char *strAudioFile = (char *)fileName;
 
	int iNbChannels 		= channels;	// 1 channel for mono, 2 channel for streo
	int iBytesPerSample = 2; 	// 16bits pcm, 2Bytes
	int frameSize 			= 0;	// frameSize = iNbChannels * iBytesPerSample
    size_t  minFrameCount 	= 0;	// get from AudroRecord object
	int iWriteDataCount = 0;	// how many data are there write to file

	sp<AudioTrack> track;
	
	ALOGD("%s  Thread ID  = %d  \n", __FUNCTION__,  pthread_self());  
	g_pAudioRecordFile = fopen(strAudioFile, "wb+");	
	
	if (iNbChannels == 2) {
		channelConfig = AUDIO_CHANNEL_IN_STEREO;
	}
	printf("sample_rate = %d, channels = %d, iNbChannels = %d, channelConfig = 0x%x\n", sample_rate, channels, iNbChannels, channelConfig);

	frameSize 	= iNbChannels * iBytesPerSample;

	status_t status = AudioRecord::getMinFrameCount(
		&minFrameCount, sampleRateInHz, audioFormat, channelConfig);

	if(status != NO_ERROR)
	{
		ALOGE("%s  AudioRecord.getMinFrameCount fail \n", __FUNCTION__);
		goto exit ;
	}

	ALOGE("sampleRateInHz = %d minFrameCount = %d iNbChannels = %d channelConfig = 0x%x frameSize = %d ", 
	sampleRateInHz, minFrameCount, iNbChannels, channelConfig, frameSize);

	bufferSizeInBytes = minFrameCount * frameSize;

	inBuffer = malloc(bufferSizeInBytes);
	if(inBuffer == NULL)
	{
		ALOGE("%s  alloc mem failed \n", __FUNCTION__);
		goto exit ;
	}

	track = new AudioTrack(AUDIO_STREAM_MUSIC, 
               sample_rate,
               AUDIO_FORMAT_PCM_16_BIT, 
               channelConfig,
               NULL);
	if(track == NULL)
	{
		ALOGE("%s  new AudioTrack failed \n", __FUNCTION__);
		goto exit ;
	}
	
	if(track->initCheck() != OK)
	{
		track.clear();
		ALOGE("AudioTrack initCheck error!");
		goto exit;
	}
	
	track->start();
	
	pAudioRecord  = new AudioRecord(
                    inputSource, sampleRateInHz, audioFormat,
                    audio_channel_in_mask_from_count(iNbChannels),
                    String16(),
                    (size_t) (frameSize * minFrameCount),
                    NULL,
                    NULL,
                    minFrameCount /*notificationFrames*/,
                    AUDIO_SESSION_ALLOCATE,
                    AudioRecord::TRANSFER_DEFAULT,
                    AUDIO_INPUT_FLAG_NONE,
                    -1,
                    -1);
	if(NULL == pAudioRecord)
	{
		ALOGE(" create native AudioRecord failed! ");
		goto exit;
	}
	
	if(pAudioRecord->initCheck() != OK)
	{
		ALOGE("AudioRecord initCheck error!");
		goto exit;
	}

	if(pAudioRecord->start()!= android::NO_ERROR)
	{
		ALOGE("AudioTrack start error!");
		goto exit;
	}
	

	while (1)
	{
		int readLen = pAudioRecord->read(inBuffer, bufferSizeInBytes);		
		int writeResult = -1;

		if(readLen > 0) 
		{
			iWriteDataCount += readLen;
			if(NULL != g_pAudioRecordFile)
			{
				writeResult = fwrite(inBuffer, 1, readLen, g_pAudioRecordFile);				
				if(writeResult < readLen)
				{
					ALOGE("Write Audio Record Stream error");
				}
			}
			//ALOGD("readLen = %d  writeResult = %d  iWriteDataCount = %d", readLen, writeResult, iWriteDataCount);			
		}
		else 
		{
			ALOGE("pAudioRecord->read  readLen = 0");
		}
	}
exit:
	if(NULL != g_pAudioRecordFile)
	{
		fflush(g_pAudioRecordFile);
		fclose(g_pAudioRecordFile);
		g_pAudioRecordFile = NULL;
	}

	if(pAudioRecord)
	{
		pAudioRecord->stop();
		//delete pAudioRecord;
		//pAudioRecord == NULL;
	}

	if(inBuffer)
	{
		free(inBuffer);
		inBuffer = NULL;
	}

	ALOGD("%s  Thread ID  = %d  quit\n", __FUNCTION__,  pthread_self());
	return NULL;
}

int main(int argc, char **argv)
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
						
	minFrameCount = 1600;					
						
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
	
	track->setVolume(2.0f, 2.0f);
	
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
	void *inBuffer1 = malloc(bufferSizeInBytes);
	ALOGE("bufferSizeInBytes=%d, %d %d", bufferSizeInBytes, minFrameCount1, minFrameCount2);
	
	int fdread = open(argv[1], O_RDONLY);
	int fdwrite = open(argv[2], O_RDWR|O_CREAT, 0644);
	
	ALOGE("fdread=%d fdwrite=%d", fdread, fdwrite);
	
	if(fdread < 0 || fdwrite < 0)
		return -1;
	
	int readLen;
	while(1)
	{
		if(read(fdread, inBuffer, 320) > 0)
		{
			track->write(inBuffer, 320);
		}
		else
		{
			break;
		}
		
		record->read(inBuffer1, 320);
		write(fdwrite, inBuffer1, 320);
	}
	
	close(fdread);
	close(fdwrite);
	record->stop();
	track->stop();
	
	return 0;
}

