LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += external/webrtc
LOCAL_SRC_FILES:= webrtctest.c
LOCAL_SHARED_LIBRARIES := libwebrtc_audio_preprocessing
LOCAL_MODULE := webrtctest
include $(BUILD_EXECUTABLE)
