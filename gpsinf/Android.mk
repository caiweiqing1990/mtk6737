LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= $(call all-c-files-under)
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE := gps_test
include $(BUILD_EXECUTABLE)

