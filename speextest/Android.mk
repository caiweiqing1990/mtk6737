LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += external/speex/include/
LOCAL_STATIC_LIBRARIES += libspeex 
LOCAL_SRC_FILES:= testecho.c
LOCAL_MODULE := testecho
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES += external/speex/include/
LOCAL_STATIC_LIBRARIES += libspeex 
LOCAL_SRC_FILES:= testlock.c
LOCAL_MODULE := testlock
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)
