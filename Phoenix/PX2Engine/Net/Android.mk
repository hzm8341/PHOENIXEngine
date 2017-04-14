LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Net

LOCAL_CPP_EXTENSION := .cc  .cpp 

LOCAL_SRC_FILES := \
PX2IPAddress.cpp \
PX2IPAddressImpl.cpp \
PX2IPv4AddressImpl.cpp \
PX2IPv6AddressImpl.cpp \
PX2IPv4SocketAddressImpl.cpp \
PX2IPv6SocketAddressImpl.cpp \
PX2SocketAddress.cpp \
PX2SocketAddressImpl.cpp \
PX2DNS.cpp \
PX2HostEntry.cpp \
PX2NetClientConnector.cpp \
PX2NetEventBuffer.cpp \
PX2NetInitTerm.cpp \
PX2NetError.cpp \
PX2Socket.cpp \
PX2SocketImpl.cpp \
PX2StreamSocket.cpp \
PX2StreamSocketImpl.cpp \
PX2ServerInfo.cpp\
PX2ServerInfoManager.cpp\
PX2NetServerPoll.cpp\
PX2ClientContext.cpp\
PX2NetServerImp.cpp \
PX2ServerSocket.cpp \
PX2ServerSocketImpl.cpp \
PX2NetServer.cpp \
PX2NetServerBuffer.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(PX2_ROOT)/PX2Engine/Unity/ \
$(PX2_ROOT)/PX2SDK/Include/

LOCAL_CPPFLAGS := -std=c++11
LOCAL_LDLIBS := -llog -pthread

include $(BUILD_STATIC_LIBRARY)
