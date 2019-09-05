LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#LOCAL_CFLAGS += 
LOCAL_C_INCLUDES += system/core/include/cutils/  $(LOCAL_PATH)/webrtc
LOCAL_SRC_FILES:= $(call all-c-files-under)
LOCAL_SRC_FILES+= $(call all-cpp-files-under)
LOCAL_STATIC_LIBRARIES += 
LOCAL_SHARED_LIBRARIES := libcutils libutils liblog
LOCAL_LDFLAGS := 
LOCAL_MODULE := WebRtcAudioTest
LOCAL_MULTILIB := 32
LOCAL_CFLAGS_arm := \
    '-DWEBRTC_POSIX' \
    '-DWEBRTC_LINUX' \
    '-DWEBRTC_THREAD_RR' \
    '-DWEBRTC_CLOCK_TYPE_REALTIME' \
    '-DWEBRTC_ANDROID' \
	'-DWEBRTC_ARCH_ARM'
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)
