LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	AudioRecordTest.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
    libmedia

LOCAL_MODULE:= AudioRecordTest

LOCAL_MODULE_TAGS := tests
include $(BUILD_EXECUTABLE)
