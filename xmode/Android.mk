LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += system/core/include/cutils
LOCAL_SRC_FILES:= $(call all-c-files-under)
LOCAL_MODULE := xmode
LOCAL_SHARED_LIBRARIES := libc
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)

