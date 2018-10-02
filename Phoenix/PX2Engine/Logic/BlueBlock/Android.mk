LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Blueblock

FILE_LIST := $(wildcard $(LOCAL_PATH)/*cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%) \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/ToScript/ \
$(PX2_ROOT)/PX2Engine/Unity/ \
$(PX2_ROOT)/PX2Engine/Unity/Lua/ \
$(PX2_ROOT)/PX2Engine/Unity/ToLua/ \
$(PX2_ROOT)/PX2Engine/Unity/LuaPlus/ \
$(PX2_ROOT)/PX2SDK/Include/

LOCAL_CFLAGS := -D__ANDROID__
LOCAL_CPPFLAGS := -frtti -std=c++11 -fexceptions -LUAPLUS_EXCEPTIONS

include $(BUILD_STATIC_LIBRARY)
