LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#LOCAL_CFLAGS += 

LOCAL_C_INCLUDES += system/core/include/cutils/ external/speex/include/
LOCAL_SRC_FILES:= $(call all-c-files-under)

LOCAL_SHARED_LIBRARIES += liblog
#LOCAL_SHARED_LIBRARIES := -llog
LOCAL_LDFLAGS += $(LOCAL_PATH)/libspeex.a

LOCAL_MODULE_TAGS := debug
LOCAL_MODULE := satfi
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin
include $(BUILD_EXECUTABLE)

