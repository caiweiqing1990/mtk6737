LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= pcm_test.c
LOCAL_MODULE := pcm_test
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)
