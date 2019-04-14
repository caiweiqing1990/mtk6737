LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= $(call all-c-files-under)
LOCAL_MODULE := jsontest
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)
