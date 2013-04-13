//
//  AstarNode.h
//  isometric
//
#ifndef ISO_CCISOTileMap_H_
#define ISO_CCISOTileMap_H_

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
 * 
 * batch compoent>componet>batch>normal
 * 关于layer层的优化。
 * 上层的layer会挡住下层的layer所以只需要显示上层的layer块。如果上层是透明的，那么可以只渲染上层的元素。但是透明的就不可以使用，如果不显示下层，会出现空洞。
 */
class CCISOTileMap : public CCNode,public CCISODynamicComponentUpdateDelegator{

public:
	
	CCISOTileMap();
    
	~CCISOTileMap();
    
    static CCISOTileMap* createWithXMLFile(const char* xmlFile);
    
    static CCISOTileMap* createWithXML(const char* xmlString,const char* resourcePath);
    
    static CCISOTileMap* createWithJSONFile(const char* mapFile);
    
    static CCISOTileMap* createWithJSON(const char* jsonString,const char* resourcePath);
	
    bool init();
    
    bool initWithXMLFile(const char* xmlFile);
    
    bool initWithJSONFile(const char* jsonFile);
    
    bool initWithXML(const char* xmlString,const char* resourcePath);
    
    bool initWithJSON(const char* jsonString,const char* resourcePath);
    
    /**
     * 取得贴图
     */
	CCISOTileset* tilesetNamed(const char* tilesetName);
    
    /**
     * 取得普通层
     */
	CCISOTileLayer* layerNamed(const char* layerName);
    
    /**
     * 取得对象层
     */
    CCISOObjectGroup* objectGroupNamed(const char *objectGroupName);
    
    
    /**
     * 取得属性
     */
	CCString *propertyNamed(const char *propertyName);

   
    void updateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY);
    
    virtual CCISOTileLayer* createLayer();
    
    void scrollLayer(const CCPoint& pos);
    
    
public://==============属性===============//
    
	virtual void setMapSize(CCSize tMapSize);
    
	virtual CCSize getMapSize();
    
    virtual void setTileSize(const CCSize& tTileSize);
    
    virtual const CCSize& getTileSize();

	virtual void setName(const char* pName);
    
	virtual const char* getName();
    
    virtual void setMapOrientation(int nMapOrientation);
    
    virtual int getMapOrientation();
    
    virtual void setTileLayers(CCArray* pTileLayers);
    
    virtual CCArray* getTileLayers();
    
    virtual void setObjectGroups(CCArray* pObjectGroups);
    
    virtual CCArray* getObjectGroups();
    
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setIdentifier(int nIdentifier);
    
    virtual int getIdentifier();
    
    virtual void setTileProperties(CCDictionary* pTileProperties);
    
    virtual CCDictionary* getTileProperties();
    
    virtual void setDynamicComponent(CCISODynamicComponent* pDynamicComponent);
    
    virtual CCISODynamicComponent* getDynamicComponent();
    
    virtual void setTilesetGroup(CCISOTilesetGroup* pTilesetGroup);
    
    virtual CCISOTilesetGroup* getTilesetGroup();
    
protected:
    
//    virtual CCISOTileLayer * parseLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
//    
//    virtual CCISOTilesetInfo * tilesetForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
//    
//    virtual void buildWithMapInfo(CCISOMapInfo* mapInfo);
//    
//    /**
//     * 主要是构建tile layer
//     */
//    virtual void buildMapLayers(CCISOMapInfo* mapInfo);
    
protected:
    /**
     * 地图大小，格子数，单位为格子。
     */
	CCSize m_tMapSize;
    
    /**
     * 地图格子大小。
     */
    CCSize m_tTileSize;
    
    /**
     * 地图名称
     */
    std::string m_pName;
    
    /**
     * 地图编号
     */
    int m_nIdentifier;
    
    /**
     * 地图类型
     */
    int m_nMapOrientation;
    
    /**
     * 图块合集
     */
    CCISOTilesetGroup* m_pTilesetGroup;
    
    /**
     * 对像分组
     */
    CCArray* m_pTileLayers;
    
    /**
     * 对像分组
     */
    CCArray* m_pObjectGroups;
    
    /**
     * 属性列表
     */
    CCDictionary* m_pProperties;
    
    /**
     * tile properties
     */
    CCDictionary* m_pTileProperties;
    
    CCISODynamicComponent* m_pDynamicComponent;
    
};



NS_CC_END

#endif //ISO_CCIOSTileMap_H_
