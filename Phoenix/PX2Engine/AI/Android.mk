LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := AI

FILE_LIST := $(wildcard $(LOCAL_PATH)/*cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/OpenSteer/src/*cpp) \
FILE_LIST += $(wildcard $(LOCAL_PATH)/iiiroboticslidar2/*cpp) \
FILE_LIST += $(wildcard $(LOCAL_PATH)/SkillSystem/*cpp) \

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%) 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(LOCAL_PATH)/../Physics/ \
$(LOCAL_PATH)/../Physics/OpenSteer/include/ \
$(LOCAL_PATH)/../Physics/Bullet/ \
$(LOCAL_PATH)/../Physics/Bullet/LinearMath/ \
$(LOCAL_PATH)/../Physics/Bullet/BulletCollision/ \
$(LOCAL_PATH)/../Physics/Bullet/BulletDynamics/ \
$(LOCAL_PATH)/OpenSteer/include/ \
$(LOCAL_PATH)/iiiroboticslidar2/ \
$(LOCAL_PATH)/SkillSystem/ \
$(PX2_ROOT)/PX2SDK/Include/ \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_CFLAGS := -D__ANDROID__ 
LOCAL_CPPFLAGS := -frtti -std=c++11 -fexceptions

include $(BUILD_STATIC_LIBRARY)
