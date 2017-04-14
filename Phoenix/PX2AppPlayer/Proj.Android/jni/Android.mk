LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

PROJECT_NAME := Block

LOCAL_MODULE := AppPlay

FILE_LIST := $(wildcard $(LOCAL_PATH)/*cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_WHOLE_STATIC_LIBRARIES := Core
LOCAL_WHOLE_STATIC_LIBRARIES += Mathematics
LOCAL_WHOLE_STATIC_LIBRARIES += Graphics
LOCAL_WHOLE_STATIC_LIBRARIES += Unity
LOCAL_WHOLE_STATIC_LIBRARIES += Net
LOCAL_WHOLE_STATIC_LIBRARIES += Effect
LOCAL_WHOLE_STATIC_LIBRARIES += Terrains
LOCAL_WHOLE_STATIC_LIBRARIES += UI
LOCAL_WHOLE_STATIC_LIBRARIES += Logic
LOCAL_WHOLE_STATIC_LIBRARIES += Application
LOCAL_WHOLE_STATIC_LIBRARIES += PX2AppPlayer
LOCAL_WHOLE_STATIC_LIBRARIES += $(PROJECT_NAME)

LOCAL_SHARED_LIBRARIES := fmod

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
$(PX2_ROOT)/ThirdPartiesLibs/OGLES/ \
$(PX2_ROOT)/PX2AppPlayer/ \
$(PX2_ROOT)/PX2AppPlayer/AppFrame/ \
$(PX2_ROOT)/PX2Engine/Unity/AppPlay/ \
$(PX2_ROOT)/PX2SDK/Include/

include $(BUILD_SHARED_LIBRARY)

$(call import-module, Core)
$(call import-module, Mathematics)
$(call import-module, Graphics)
$(call import-module, Unity)
$(call import-module, Net)
$(call import-module, Effect)
$(call import-module, Terrains)
$(call import-module, UI)
$(call import-module, Logic)
$(call import-module, Application)
$(call import-module, PX2AppPlayer)
$(call import-module, $(PROJECT_NAME))

#ProjHULL
#include $(CLEAR_VARS)
#LOCAL_MODULE := ProjHULL
#LOCAL_WHOLE_STATIC_LIBRARIES := $(PROJECT_NAME)
#include $(BUILD_SHARED_LIBRARY)
#$(call import-module, $(PROJECT_NAME))