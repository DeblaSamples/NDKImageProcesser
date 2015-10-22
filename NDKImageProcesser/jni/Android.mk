LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NDKProcesser
LOCAL_SRC_FILES := com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser.cpp \
				   Log.cpp \
				   NDKProcesser.cpp

LOCAL_LDLIBS    += -ljnigraphics -llog
include $(BUILD_SHARED_LIBRARY)
