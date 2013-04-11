//
//  AstarNode.h
//  isometric
//
#ifndef ISO_CCISOTileMapBuilder_H_
#define ISO_CCISOTileMapBuilder_H_

#include "cocos2d.h"
#include "CCISOMapInfo.h"
#include "CCISOObjectGroupInfo.h"
#include "CCISOObjectInfo.h"
#include "CCISOLayerInfo.h"
#include "CCISOTileInfo.h"
#include "CCISOTilesetInfo.h"

#include "CCISOTileLayer.h"
#include "CCISODynamicComponent.h"

#include "CCISOObjectGroup.h"
#include "CCISOTilesetGroup.h"



NS_CC_BEGIN

class CCISOTileMap;
/**
 * 地图分为二种层。
 * 一种是图块图层，通常只显示图形，覆盖整个地图坐标。通常坐为背景层或地表层，主要是静态的物体。
 * 一种是对象层，只记录出层的对象，对象包含出现在地图上的坐标和大小等。通常坐为中间层，显示人物，怪物，一些做为背景动态的东西，如动态水面，地上的火焰。
 * 
 * 注意:这里的实现和tmx里的实现不太一样,
 * tmx里tile layer是直接添加到显示子列表里，object layer做为属性，具体怎么用由游戏决定。
 * 这里都做为属性，具体怎么用由游戏来决定
 */
class CCISOTileMapBuilder : public CCObject{

public:
	
	CCISOTileMapBuilder();
    
	~CCISOTileMapBuilder();
    
    virtual bool init();
    
    virtual bool init(CCISOTileMap* pMap);
    
    virtual void buildWithMapInfo(CCISOMapInfo* mapInfo);
    
    /**
     * 构建tilesets
     */
    virtual void buildMapTilesets(CCISOMapInfo* mapInfo);
    
    /**
     * 构建tileset
     */
    virtual void buildMapTileset(CCISOTilesetInfo* tilesetInfo,CCISOTilesetGroup* tilesetGroup);
    
    /**
     * 构建tiles
     */
    virtual void buildMapTiles(CCArray* tileInfos,CCISOTileset* tileset);
    
    /**
     * 设置tile属性
     */
    virtual void setMapTilesProperties(CCArray* tileInfos,CCISOTileset* tileset);
    /**
     * 构建object groups
     */
    virtual void buildMapObjectGroups(CCISOMapInfo* mapInfo);
    /**
     * 构建objects
     */
    virtual void buildMapObjects(CCArray* objects,CCISOObjectGroup* objectGroup);
    /**
     * 构建map object
     */
    virtual void buildMapObject(CCISOObjectInfo* objectInfo,CCISOObjectGroup* objectGroup);
    
    /**
     * 构建tile layer
     */
    virtual void buildMapLayers(CCISOMapInfo* mapInfo);
    
    virtual void buildMapLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);

    virtual void setLayerAttribute(CCISOTileLayer* tileLayer,CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    virtual CCISOTileset * tilesetForLayer(CCISOLayerInfo *layerInfo);
    
    virtual CCISOTilesetInfo * tilesetInfoForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
public:
    
    inline void setMap(CCISOTileMap* pMap){
        m_pMap=pMap;
    }
    
    inline CCISOTileMap* getMap(){
        return m_pMap;
    }
    
    inline void setMapLayerType(unsigned int uMapLayerType)
    {
        m_uMapLayerType = uMapLayerType;
    }
    
    inline unsigned int getMapLayerType()
    {
        return m_uMapLayerType;
    }
   
public:
    
    enum BuildMapLayerType{
        NormalLayerType,
        DynamicLayerType,
        BatchLayerType
    };
    
protected:
    
    CCISOTileMap* m_pMap;
    
    unsigned int m_uMapLayerType;
    
};



NS_CC_END

#endif //ISO_CCISOTileMapBuilder_H_
