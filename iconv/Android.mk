LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := libiconv
LOCAL_SRC_FILES := iconv.c
include $(BUILD_STATIC_LIBRARY)
