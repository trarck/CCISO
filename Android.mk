LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_common

LOCAL_MODULE_FILENAME := libgamecommon

LOCAL_SRC_FILES := \
Classes/Message/CCMessageHandler.cpp \
Classes/Message/CCMessage.cpp \
Classes/Message/CCMessageManager.cpp \
Classes/Isometric/CCCoordinate.cpp  \
Classes/Isometric/CCAstarNode.cpp \
Classes/Isometric/CCAstar.cpp \
Classes/Isometric/CCZIndexNode.cpp \
Classes/Isometric/CCZIndex.cpp \
Classes/Isometric/CCISOTileLayer.cpp \
Classes/Isometric/CCISOTileLayerOptimization.cpp \
Classes/Isometric/CCISOComponentNode.cpp \
Classes/Isometric/CCISOTileLayerDynamicComponent.cpp \
Classes/Components/Component.cpp \
Classes/Components/AttackComponent.cpp \
Classes/Components/AutoAttackComponent.cpp \
Classes/Components/ManualAttackComponent.cpp \
Classes/Components/AnimationComponent.cpp \
Classes/Components/GridMoveComponent.cpp \
Classes/Entities/GameEntity.cpp \
Classes/Entities/WorldEntity.cpp \
Classes/Entities/Unit.cpp \
Classes/Entities/Monster.cpp \
Classes/Entities/Player.cpp  \
Classes/Layers/ISOCoordinateLayer.cpp  \
Classes/Scenes/GameStartScene.cpp \
Classes/Scenes/GameScene.cpp \
Classes/Scenes/GameOverScene.cpp  \
Classes/AppDelegate.cpp \
Classes/GameCamera.cpp \
Classes/GameWorld.cpp 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/Classes \
$(LOCAL_PATH)/Classes/Message \
$(LOCAL_PATH)/Classes/Isometric \
$(LOCAL_PATH)/Classes/Components \
$(LOCAL_PATH)/Classes/Entities \
$(LOCAL_PATH)/Classes/Layers \
$(LOCAL_PATH)/Classes/Scenes 

LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv2

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
$(LOCAL_PATH)/Classes \
$(LOCAL_PATH)/Classes/Message \
$(LOCAL_PATH)/Classes/Isometric \
$(LOCAL_PATH)/Classes/Components \
$(LOCAL_PATH)/Classes/Entities \
$(LOCAL_PATH)/Classes/Layers \
$(LOCAL_PATH)/Classes/Scenes 

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)