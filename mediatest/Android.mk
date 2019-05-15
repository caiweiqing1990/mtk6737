LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:=libmediatest
LOCAL_SRC_FILES:=libmediatest.so
include $(PREBUILT_SHARED_LIBRARY)
