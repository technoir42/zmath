LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := zmath
LOCAL_CPPFLAGS := -std=c++11
LOCAL_SRC_FILES := zmath/zmath.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)
