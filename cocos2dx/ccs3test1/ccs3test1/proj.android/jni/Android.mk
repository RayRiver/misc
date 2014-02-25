LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/B2Sprite.cpp \
                   ../../Classes/Barrier.cpp \
                   ../../Classes/Box2dTest.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../Classes/Helicopter.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/VisibleRect.cpp 

# 遍历目录及子目录的函数
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

# 遍历Classes目录
#LOCAL_SRC_FILES := $(call walk, $(LOCAL_PATH)/../../Classes)
#LOCAL_SRC_FILES += hellocpp/main.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/cocos/editor-support
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/extensions
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d/external/raknet

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_gui_static
LOCAL_WHOLE_STATIC_LIBRARIES += raknet_static


include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../cocos2d)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path, $(LOCAL_PATH)/../../cocos2d/external)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)
$(call import-module,gui)
$(call import-module,editor-support/cocostudio)
$(call import-module,raknet)


