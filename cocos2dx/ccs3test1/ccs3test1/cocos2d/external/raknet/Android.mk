LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := raknet_static

LOCAL_MODULE_FILENAME := libraknet

# 遍历目录及子目录的函数
define walk
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

# 遍历Classes目录
LOCAL_SRC_FILES := $(call walk, $(LOCAL_PATH))

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)
                                 
include $(BUILD_STATIC_LIBRARY)
