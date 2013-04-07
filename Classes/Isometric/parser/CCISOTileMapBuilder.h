//
//  AstarNode.h
//  isometric
//
#ifndef ISO_CCISOTileMapBuilder_H_
#define ISO_CCISOTileMapBuilder_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"
#include "CCISOObjectGroup.h"
//#include "CCISOXMLParser.h"
#include "CCISODynamicComponent.h"
#include "CCISOTilesetGroup.h"


NS_CC_BEGIN

/**
 * 地图分为二种层。
 * 一种是图块图层，通常只显示图形，覆盖整个地图坐标。通常坐为背景层或地表层，主要是静态的物体。
 * 一种是对象层，只记录出层的对象，对象包含出现在地图上的坐标和大小等。通常坐为中间层，显示人物，怪物，一些做为背景动态的东西，如动态水面，地上的火焰。
 * 
 * 注意:这里的实现和tmx里的实现不太一样,
 * tmx里tile layer是直接添加到显示子列表里，object layer做为属性，具体怎么用由游戏决定。
 * 这里都做为属性，具体怎么用由游戏来决定
 */
class CCISOTileMapBuilder : public CCNode,public CCISODynamicComponentUpdateDelegator{

public:
	
	CCISOTileMapBuilder();
    
	~CCISOTileMapBuilder();
    
       
    virtual CCISOTileLayer * parseLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    virtual CCISOTilesetInfo * tilesetForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    virtual void buildWithMapInfo(CCISOMapInfo* mapInfo);
    
    /**
     * 主要是构建tile layer
     */
    virtual void buildMapLayers(CCISOMapInfo* mapInfo);
    
protected:
    
    
};



NS_CC_END

#endif //ISO_CCISOTileMapBuilder_H_
