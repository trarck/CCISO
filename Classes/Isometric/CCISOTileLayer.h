#ifndef ISO_CCISOTileLayer_H_
#define ISO_CCISOTileLayer_H_

#include "cocos2d.h"
#include "CCISOMapInfo.h"
#include "CCISOTilesetInfo.h"
#include "CCISOLayerInfo.h"

NS_CC_BEGIN

class CCISOTileMap;

/**
 * tile layer 图块图层。
 * 没有复杂的游戏逻辑，通常只做显示。
 * 只显示图形，覆盖整个地图坐标。
 * 坐为背景层或地表层，主要是静态的物体。
 */

class CCISOTileLayer : public CCNode {

public:
	
	CCISOTileLayer();
    
	~CCISOTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);
    
    static CCISOTileLayer* create();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();

    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    
    virtual void initOffset(float x,float y);
    
    /**
     * 添加tile
     */
    virtual void addTile(CCSprite* tile);
    
    virtual void addTileAt(CCSprite* tile,float x,float y);
    
	virtual void addTileAt(CCSprite* tile,const CCPoint& tileCoordinate);


    /**
     * 获取tile
     */
	virtual CCSprite* tileAt(float x,float y);
    
	virtual CCSprite* tileAt(const CCPoint& tileCoordinate);
    
    /**
     * 删除tile
     */
    virtual void removeTile(CCSprite* tile);
    
	virtual void removeTileAt(float x,float y);
    
    virtual void removeTileAt(const CCPoint& pos);
 
    //移动
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
    
    /**
     * 获取属性名称
     */
    CCString *propertyNamed(const char *propertyName);
    
    //===================get set 属性====================//
    
	virtual void setLayerSize(const CCSize& tLayerSize);
    
	virtual CCSize getLayerSize();

    virtual void setMapTileSize(const CCSize& tMapTileSize);
    
    virtual void setMapTileSize(float width,float height);
    
    virtual const CCSize& getMapTileSize();

	virtual void setOffset(const CCPoint& tOffset);
    
	virtual void setOffset(float x,float y);
    
	virtual CCPoint getOffset();
    
    inline const char* getLayerName(){ return m_sLayerName.c_str(); }
    
    inline void setLayerName(const char *layerName){ m_sLayerName = layerName; }
       
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setLayerOrientation(unsigned int uLayerOrientation);
    
    virtual unsigned int getLayerOrientation();
    
    virtual void setTiles(unsigned int* pTiles);
    
    virtual unsigned int* getTiles();
    
    inline void setMap(CCISOTileMap* pMap)
    {
        m_pMap = pMap;
    }
    
    inline CCISOTileMap* getMap()
    {
        return m_pMap;
    }
    
protected:
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
            
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
protected:
    
    /**
     * 层的名称
     */
    std::string m_sLayerName;
    
    /**
     * 层的地图大小
     */
	CCSize m_tLayerSize;
    
    /**
      地图的一个图块大小
     */
    CCSize m_tMapTileSize;
    
    unsigned int* m_pTiles;
    
    CCArray* m_pTilesetInfos;
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint m_tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int m_iStartX;
	int m_iStartY;
    
    /**
     * 地图属性
     */
    CCDictionary* m_pProperties;
       
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int m_uLayerOrientation;
    
    //! Layer supports opacity
    unsigned char       m_cOpacity;
    
    //! Only used when vertexZ is used
    int                 m_nVertexZvalue;
    
    bool                m_bUseAutomaticVertexZ;
        
    // used for retina display
    float               m_fContentScaleFactor;

    CCISOTileMap* m_pMap;
};


NS_CC_END

#endif //ISO_CCISOTileLayer_H_
