
#include <media/AudioRecord.h>
#include <media/AudioTrack.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "satfi.h"
#ifdef __cplusplus
}
#endif

using namespace android;

extern BASE base;
extern char satfi_version[32];
#define BUS_SIZE (6*960)//11520

int audio_test(void)
{
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

void milliseconds_sleep()
{
  struct timeval tv = {0, 20000};//20ms
  int err;
  do
  {
    err = select(0,NULL,NULL,NULL,&tv);
  } while (err<0 || errno == EINTR);
}

void *handle_pcm_data(void *p)
{
	BASE *base = (BASE *)p;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12070);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        satfi_log("socket udp error");
        exit(1);
    }

    unsigned int value = 1;  
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,  
                (void *)&value, sizeof(value)) < 0)  
    {  
        satfi_log("fail to setsockopt\n");  
		close(sock);		
        exit(1);  
    }

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        satfi_log("bind udp error");
		close(sock);
        exit(1);
    }

	char tmp[BUS_SIZE];
	char outfram[BUS_SIZE];
	//char playbackbuf[3200];
	int plybackbufofs=0;
	struct sockaddr_in clientAddr;
	struct sockaddr_in *clientAddr1 = &(base->sat.clientAddr1);
	struct sockaddr_in *clientAddr2 = &(base->sat.clientAddr2);

	base->sat.voice_socket_udp = sock;

	socklen_t len = sizeof(struct sockaddr_in);
	
	bzero(&clientAddr, len);
	bzero(clientAddr1, len);
	bzero(clientAddr2, len);
	
	int n;
	struct timeval tout = {10,0};	
	fd_set fds;
	int maxfd;
	int ret;
	int ofs=0,ofs1=0;

	satfi_log("select_voice_udp %d\n", sock);

	//SpeexPreprocessState *st;
	//st = speex_preprocess_state_init(NN, 8000);

	//int vad = 1;
	//int vadProbStart = 90;
	//int vadProbContinue = 100;
	//speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_VAD, &vad); //静音检测
	//speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_PROB_START , &vadProbStart); //Set probability required for the VAD to go from silence to voice
	//speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_PROB_CONTINUE, &vadProbContinue); //Set probability required for the VAD to stay in the voice state (integer percent)

	size_t  minFrameCount 	= 0;
	int framesize = 2;
	
	sp<AudioRecord> record = new AudioRecord(AUDIO_SOURCE_MIC, 8000, AUDIO_FORMAT_PCM_16_BIT, audio_channel_in_mask_from_count(1),
						String16(),(size_t)(2 * framesize * BUS_SIZE), NULL, NULL, minFrameCount, AUDIO_SESSION_ALLOCATE,
						AudioRecord::TRANSFER_DEFAULT, AUDIO_INPUT_FLAG_NONE, -1, -1);
	if(record->initCheck() != OK)
	{
		satfi_log("AudioRecord initCheck error!");
	}	

	int AudioRecordStart = 0;

	//SpeexEchoState *st;
	//SpeexPreprocessState *den;
	//int sampleRate = 8000;

	//st = speex_echo_state_init(NN, TAIL);
	//den = speex_preprocess_state_init(NN, sampleRate);
	//speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
	//speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);

	while (1)
    {
		FD_ZERO(&fds);/* 每次循环都需要清空 */
		FD_SET(sock, &fds); /* 添加描述符 */
		maxfd = sock;
		tout.tv_sec = 3;
		tout.tv_usec = 0;
		
		switch(select(maxfd+1,&fds,NULL,NULL,&tout))
		{
			case -1: break;
			case  0:
				
				if(base->sat.secondLinePhoneMode == 0)
				{
					if(base->sat.sat_calling == 1)
					{
						satfi_log("clientAddr timeout\n");
						if(base->sat.sat_state_phone == SAT_STATE_PHONE_DIALING_RING)
						{
							if(ntohs(clientAddr1->sin_port) == 0)
							{
								AppCallUpRspForce(base->sat.socket, SAT_STATE_PHONE_DIALING_RING);
							}
						}
						else if(base->sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
						{
							if(ntohs(clientAddr1->sin_port) == 0)
							{
								AppCallUpRspForce(base->sat.socket, SAT_STATE_PHONE_DIALING_RING);
								AppCallUpRspForce(base->sat.socket, SAT_STATE_PHONE_ONLINE);
							}
						}
						break;
					}
					
					if(ntohs(clientAddr1->sin_port) != 0 && ntohs(clientAddr2->sin_port) != 0)
					{
						base->sat.sat_state_phone = SAT_STATE_PHONE_IDLE;
					}
					else if(ntohs(clientAddr1->sin_port) != 0)
					{
						base->sat.sat_calling = 0;
						base->sat.sat_state_phone = SAT_STATE_PHONE_IDLE;
					}
					
					if(ntohs(clientAddr1->sin_port) != 0)
					{
						satfi_log("bzero clientAddr1\n");
						bzero(clientAddr1, len);
					}
					
					if(ntohs(clientAddr2->sin_port) != 0)
					{
						satfi_log("bzero clientAddr2\n");
						bzero(clientAddr2, len);
					}

					plybackbufofs = 0;
					
					if(AudioRecordStart == 1)
					{
						AudioRecordStart = 0;
						record->stop();
					}
				}
				
				break;
			default:
								
				if(FD_ISSET(sock, &fds))
				{
			        n = recvfrom(sock, &tmp[ofs], 320, 0, (struct sockaddr*)&clientAddr, &len);
			        if (n>0 && base->sat.sat_calling == 1)
			        {
						if(memcmp(clientAddr1 ,&clientAddr, len) == 0)
						{
							if(ntohs(clientAddr2->sin_port) != 0)
							{
								if(base->sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
								{
									n = sendto(sock, tmp, n, 0, (struct sockaddr *)clientAddr2, len);
									if (n < 0)
									{
										perror("sendto clientAddr2");
									}
								}
							}
							else
							{
								if(base->sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
								{
									if(base->sat.sat_pcmdata > 0)
									{
										//satfi_log("n=%d ofs=%d\n", n, ofs);
										ofs += n;
										if(ofs >= BUS_SIZE)
										{
											ofs1=0;
											while(ofs1<ofs)
											{
												if(write(base->sat.sat_pcmdata, &tmp[ofs1], 320) <= 0)
												{
													satfi_log("write sat_pcmdata error\n");
													continue;
												}
												//satfi_log("%d\n", ofs1);
												ofs1 += 320;
												milliseconds_sleep(); //delay 20ms
											}
											//gettimeofday(&end, NULL);
											//satfi_log("ofs1=%d %ld\n", ofs1, end.tv_usec);
											ofs = 0;
										}
									}
									else
									{
										satfi_log("recvfrom_app_voice_udp = %d\n", base->sat.sat_pcmdata);
									}									
								}
								else
								{
									plybackbufofs = 0;
								}
							}
						}
						else if(memcmp(clientAddr2 ,&clientAddr, len) == 0)
						{
							if(ntohs(clientAddr1->sin_port) != 0 && base->sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
							{
								//gettimeofday(&tv, NULL);
								//satfi_log("%s %d %06d %d",inet_ntoa(clientAddr2->sin_addr) ,tv.tv_sec, tv.tv_usec, n);
								n = sendto(sock, tmp, n, 0, (struct sockaddr *)clientAddr1, len);
								if (n < 0)
								{
									perror("sendto clientAddr1");
								}
							}
						}
						else
						{
							if(ntohs(clientAddr1->sin_port) == 0)
							{
								satfi_log("clientAddr1 %s %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
								memcpy(clientAddr1, &clientAddr, len);
							}
							else if(ntohs(clientAddr2->sin_port) == 0)
							{
								satfi_log("clientAddr2 %s %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
								memcpy(clientAddr2, &clientAddr, len);
							}
							else
							{
								satfi_log("%s %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
							}
						}
			        }					
				}
		}

		while(base->sat.secondLinePhoneMode == 1)
		{
			if(base->sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
			{
				if(AudioRecordStart == 0)
				{
					AudioRecordStart = 1;
					if(record->start() != android::NO_ERROR)
					{
						satfi_log("AudioRecord start error!");
						record.clear();
					}
				}

				record->read(tmp, 320);

				if(base->sat.locak_socket_audio_cancel[1] > 0)
				{
					write(base->sat.locak_socket_audio_cancel[1], tmp, 320);
				}
				else
				{
					write(base->sat.sat_pcmdata, tmp, 320);
				}
			}
			else
			{
				sleep(1);
			}
		}
    }	
}


void main_thread_loop(void)
{
	fd_set fds;
	int maxfd = 0;
	struct timeval timeout;

	int SatDataOfs[4]={0};
	char SatDataBuf[4][4096];

	char gpsDataBuf[1024];
	int gpsSocketfd = -1;
	//int gpsSocketfd = create_satfi_udp_fd();
	//satfi_log("gpsSocketfd=%d\n", gpsSocketfd);
	//gps_start();
	
	struct sockaddr_in *clientAddr1 = &(base.sat.clientAddr1);
	socklen_t len = sizeof(struct sockaddr_in);

	int n,ret;	
	//AUDIO_CHANNEL_OUT_STEREO, 16 bit, stereo 22050 Hz
	sp<AudioTrack> track = new AudioTrack(AUDIO_STREAM_MUSIC, 8000, AUDIO_FORMAT_PCM_16_BIT, AUDIO_CHANNEL_OUT_MONO, 0);
	if(track->initCheck() != OK)
	{
		satfi_log("AudioRecord initCheck error!\n");
	}

	//track->setVolume(2.0f, 2.0f);

	int AudioTrackStart = 0;

	while(1)
	{
		FD_ZERO(&fds);
		maxfd=0;

		if(gpsSocketfd > 0) {
			FD_SET(gpsSocketfd, &fds);
			if(gpsSocketfd > maxfd) {
				maxfd = gpsSocketfd;
			}
		}

		if(base.sat.sat_fd > 0) {
			FD_SET(base.sat.sat_fd, &fds);
			if(base.sat.sat_fd > maxfd) {
				maxfd = base.sat.sat_fd;
			}
		}

		if(base.sat.sat_phone > 0) {
			FD_SET(base.sat.sat_phone, &fds);
			if(base.sat.sat_phone > maxfd) {
				maxfd = base.sat.sat_phone;
			}
		}

		if(base.sat.sat_message > 0) {
			FD_SET(base.sat.sat_message, &fds);
			if(base.sat.sat_message > maxfd) {
				maxfd = base.sat.sat_message;
			}
		}
		
		if(base.sat.sat_pcmdata > 0) {
			FD_SET(base.sat.sat_pcmdata, &fds);
			if(base.sat.sat_pcmdata > maxfd) {
				maxfd = base.sat.sat_pcmdata;
			}
		}

		if(maxfd == 0) {
			sleep(3);
			continue;
		}

		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		switch(select(maxfd+1,&fds,NULL,NULL,&timeout))
		{
			case -1: satfi_log("select error %s\n", strerror(errno)); break;
			case  0: 
			{
				if(base.sat.secondLinePhoneMode == 0)
				{
					if(AudioTrackStart == 1)
					{
						track->stop();
						AudioTrackStart = 0;
					}
				}
				break;
			}
			default:
				if(base.sat.sat_fd > 0 && FD_ISSET(base.sat.sat_fd, &fds)) {
					//satfi_log("base.sat.sat_fd=%d\n", base.sat.sat_fd);
					handle_sat_data(&base.sat.sat_fd, SatDataBuf[0], &SatDataOfs[0]);//卫星模块数据
				}

				if(base.sat.sat_phone > 0 && FD_ISSET(base.sat.sat_phone, &fds)) {
					//satfi_log("base.sat.sat_phone=%d\n", base.sat.sat_phone);
					handle_sat_data(&base.sat.sat_phone, SatDataBuf[1], &SatDataOfs[1]);//卫星模块数据
				}

				if(base.sat.sat_message > 0 && FD_ISSET(base.sat.sat_message, &fds)) {
					//satfi_log("base.sat.sat_message=%d\n", base.sat.sat_message);
					handle_sat_data(&base.sat.sat_message, SatDataBuf[2], &SatDataOfs[2]);//卫星模块数据
				}

				if(base.sat.sat_pcmdata > 0 && FD_ISSET(base.sat.sat_pcmdata, &fds)) {
					n = read(base.sat.sat_pcmdata, SatDataBuf[3], 320);
					//satfi_log("read sat_pcmdata=%d\n", n);
					if(n > 0)
					{
						if(ntohs(clientAddr1->sin_port) != 0)
						{
							//write(fd, SatDataBuf[3], n);
							ret = sendto(base.sat.voice_socket_udp, SatDataBuf[3], n, 0, (struct sockaddr *)clientAddr1, len);
							if(ret <= 0)
							{
								satfi_log("sendto clientAddr11 %s\n", strerror(errno));								
							}
							else
							{
								//satfi_log("read serial sat_pcmdata n = %d\n", n);								
							}
						}
						else
						{
							//satfi_log("clientAddr1->sin_port zero\n");
							if(base.sat.secondLinePhoneMode == 1)
							{
								if(AudioTrackStart == 0)
								{
									if(track->start() != android::NO_ERROR)
									{
										satfi_log("AudioTrack start error!");
									}
									else
									{
										satfi_log("AudioTrack start success!");
									}
									AudioTrackStart = 1;
								}

								if(base.sat.sat_state_phone == SAT_STATE_PHONE_ONLINE)
								{
									if(base.sat.locak_socket_audio_cancel[0] > 0)
									{
										write(base.sat.locak_socket_audio_cancel[0], SatDataBuf[3], n);
									}
								}
								
								track->write(SatDataBuf[3], n);
							}
						}
					}
					else
					{
						satfi_log("read sat_pcmdata error\n");
						close(base.sat.sat_pcmdata);
						base.sat.sat_pcmdata = -1;
					}
				}

				if(gpsSocketfd > 0 && FD_ISSET(gpsSocketfd, &fds))
				{
					int n = safe_recvfrom(gpsSocketfd, gpsDataBuf, 1024);
					if(n>0)
					{
						gpsDataBuf[n] = 0;
						strncpy(base.gps.gps_bd, gpsDataBuf, n);
						parseGpsData(gpsDataBuf, n);
						//satfi_log("gpsDataBuf=%s\n", gpsDataBuf);
					}
				}
				break;
		}
	}
	
}

int AudioTrackPlay(const char *filename)
{
	int framesize = 2;
	int len;
	size_t  minFrameCount = 0;
	char buf[44100];
	
	int fd = open(filename, O_RDONLY);
	if(fd < 0)
	{
		satfi_log("%s not exist\n", filename);
		return -1;
	}

	lseek(fd, 0, 44);//跳过wav头大小
	
	AudioTrack::getMinFrameCount(&minFrameCount, AUDIO_STREAM_DEFAULT, 44100);
	//satfi_log("minFrameCount = %d", (int)minFrameCount);
	sp<AudioTrack> track = new AudioTrack(AUDIO_STREAM_MUSIC, 44100, AUDIO_FORMAT_PCM_16_BIT, AUDIO_CHANNEL_OUT_STEREO, 0);
	
	if(track->initCheck() != OK)
	{
		satfi_log("AudioTrack initCheck error!");
		track.clear();
		return -1;
	}
	
	if(track->start()!= android::NO_ERROR)
	{
		satfi_log("AudioTrack start error!");
		return -1;
	}
		
	while(1)
	{
		len = read(fd, buf, 4 * minFrameCount);
		if(len > 0)
		{
			//ALOGE("len = %d", len);
			track->write(buf, len);
		}
		else
		{
			//satfi_log("%s END\n", filename);
			break;
		}
	}
	
	track->stop();
	close(fd);
	return 0;
}

void *SecondLineHintTonePlay(void *p)
{
	BASE *base = (BASE *)p;
	while(1)
	{
		if(base->sat.isSecondLinePickUp == 1)
		{
			if(base->sat.playBusyToneFlag == 1)
			{
				AudioTrackPlay(BUSY_WAV);
			}
			else
			{
				if(base->sat.ring == 0 && base->sat.isSecondLineFirstKeyPress == 0)
				{
					AudioTrackPlay(DUDU_WAV);
				}
				else
				{
					sleep(1);
				}
			}
		}
		else
		{
			base->sat.playBusyToneFlag = 0;
			sleep(1);
		}
	}
	return NULL;
}

void *local_socket_server(void *p)
{
	BASE *base = (BASE *)p;

	struct timeval timeout;
	int ret = -1;
	int max_fd = -1;
	int i;
	fd_set fds;
	fd_set fdread;
	struct sockaddr_in cli_addr;  
	int len = sizeof(struct sockaddr_in);
	char buf[2048] = {0};

	//int LocalSocketfd = android_get_control_socket("socket_audio_cancel"); //socket socket_audio_cancel stream 660 system system

	int LocalSocketfd[2] = {0};

	LocalSocketfd[0] = socket_local_server("com.hwacreate.localsocket0", ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);//发生接受到的声音
	LocalSocketfd[1] = socket_local_server("com.hwacreate.localsocket1", ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);//发送录制的声音
	satfi_log("LocalSocketfd[0]=%d LocalSocketfd[1]=%d\n", LocalSocketfd[0], LocalSocketfd[1]);

	if(LocalSocketfd[0] < 0 || LocalSocketfd[1] < 0)
	{
		perror("socket_local_server");
		return NULL;
	}
	
	FD_ZERO(&fds);
	FD_ZERO(&fdread);

	FD_SET(LocalSocketfd[0], &fdread);
	FD_SET(LocalSocketfd[1], &fdread);

	max_fd = (LocalSocketfd[0] > LocalSocketfd[1]) ? LocalSocketfd[0] : LocalSocketfd[1];

	while(1)
	{
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		fds = fdread;
		ret = select(max_fd + 1, &fds, NULL, NULL, &timeout);		
        if (ret == 0)
        {
            //int testfd0 = socket_local_client("com.hwacreate.localsocket0" , ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
			//write(testfd0, "hello", 5);
			//close(testfd0);
           // int testfd1 = socket_local_client("com.hwacreate.localsocket1" , ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
			//write(testfd1, "world", 5);
			//close(testfd1);
        }
        else if (ret < 0)
        {  
            satfi_log("LocalSocketCreate error occur\n"); 
			sleep(1);
        }
		else
		{
			for(i=0;i<2;i++)
			{
				if(FD_ISSET(LocalSocketfd[i], &fds))
				{
					if(base->sat.locak_socket_audio_cancel[i] > 0)
					{
						FD_CLR(base->sat.locak_socket_audio_cancel[i], &fdread);
						close(base->sat.locak_socket_audio_cancel[i]);
						//max_fd = LocalSocketfd;
					}
				
					base->sat.locak_socket_audio_cancel[i] = accept(LocalSocketfd[i], (struct sockaddr*)&cli_addr, &len);
					satfi_log("locak_socket_audio_cancel comes %d %d\n", i, base->sat.locak_socket_audio_cancel[i]);
					if(base->sat.locak_socket_audio_cancel[i] > 0)
					{
						FD_SET(base->sat.locak_socket_audio_cancel[i], &fdread);
						if(base->sat.locak_socket_audio_cancel[i] > max_fd)
						{
							max_fd = base->sat.locak_socket_audio_cancel[i];
						}
					}
					else
					{
						satfi_log("LocalSocketfd Fail to accept\n");
						exit(0);
					}
				}

				if(base->sat.locak_socket_audio_cancel[i] > 0)
				{
					if(FD_ISSET(base->sat.locak_socket_audio_cancel[i], &fds))
					{
						int n = read(base->sat.locak_socket_audio_cancel[i], buf, 320);
						if(n>0)
						{
							satfi_log("n=%d\n", n);
							write(base->sat.sat_pcmdata, buf, n);
						}
						else
						{
							satfi_log("close(locak_socket_audio_cancel) %d\n", i);
							FD_CLR(base->sat.locak_socket_audio_cancel[i], &fdread);
							close(base->sat.locak_socket_audio_cancel[i]);
							base->sat.locak_socket_audio_cancel[i] = -1;
							//max_fd = LocalSocketfd;
						}
					}
				}
			}
		}
	}

	return NULL;
}

int main()
{
	pthread_t id_1;	

	base.sat.active = 1;//default value
	base.sat.qos1 = 3;
	base.sat.qos2 = 384;
	base.sat.qos3 = 384;

	base.sat.sat_baud_rate = 921600;
	strcpy(base.sat.sat_dev_name, "/dev/ttygsm1");

	strcpy(satfi_version, "HTL8100 1.1");
	satfi_log("satfi_version=%s", satfi_version);
	
	hw_init();
	ttygsmcreate();
	if(pthread_create(&id_1, NULL, local_socket_server, (void *)&base) == -1) exit(1);
	if(pthread_create(&id_1, NULL, func_y, (void *)&base) == -1) exit(1);						//卫星模块启动
	if(pthread_create(&id_1, NULL, SystemServer, (void *)&base) == -1) exit(1);					//系统检测
	if(pthread_create(&id_1, NULL, handle_app_data, (void *)&base) == -1) exit(1); 				//处理app数据
	if(pthread_create(&id_1, NULL, sat_ring_detect, (void *)&base) == -1) exit(1); 				//卫星来电检测
	if(pthread_create(&id_1, NULL, SecondLineHintTonePlay, (void *)&base) == -1) exit(1);		//二线电话提示音
	if(pthread_create(&id_1, NULL, Second_linePhone_Dial_Detect, (void *)&base) == -1) exit(1);//二线电话拨号检测
	if(pthread_create(&id_1, NULL, handle_pcm_data, (void *)&base) == -1) exit(1);				//处理通话语音
	
	//init();
	main_thread_loop();
	return 0;
}
