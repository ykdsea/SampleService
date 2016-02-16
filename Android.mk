LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	ISampleService.cpp 

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog \
	libbinder 

LOCAL_MODULE:= libSampleService

include $(BUILD_SHARED_LIBRARY)
#####################################################################
# build executable
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	SampleService.cpp

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \
	libSampleService \
	libcutils \
	liblog 

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= sampleservice

include $(BUILD_EXECUTABLE)

#####################################################################
# build executable
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	SampleClient.cpp

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \
	libSampleService \
	libcutils \
	liblog 

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= sampleclient

include $(BUILD_EXECUTABLE)

