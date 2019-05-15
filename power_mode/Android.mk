LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= power_mode.c
LOCAL_MODULE := power_mode
LOCAL_MODULE_TAGS := debug
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= httpdown.c
LOCAL_MODULE := httpdown
LOCAL_MODULE_TAGS := debug
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= mtkgpio.c
LOCAL_MODULE := mtkgpio
LOCAL_MODULE_TAGS := debug
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= chat.c
LOCAL_MODULE := chat
LOCAL_MODULE_TAGS := debug
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= wifitest.c
LOCAL_MODULE := wifitest
LOCAL_MODULE_TAGS := debug
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= n_gsm.c
LOCAL_MODULE := n_gsm
LOCAL_MODULE_TAGS := debug
include $(BUILD_EXECUTABLE)

