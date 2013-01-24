#ifndef ISO_CCISOTileLayer_H_
#define ISO_CCISOTileLayer_H_

#include "cocos2d.h"
#include "CCISOMapInfo.h"
#include "CCISOTilesetInfo.h"
#include "CCISOLayerInfo.h"

NS_CC_BEGIN

class CCISOTileLayer : public CCNode {

public:
	
	CCISOTileLayer();
	~CCISOTileLayer(void);
	
    virtual bool init();
    
    virtual void releaseMap();

    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);

    /**
     * 获取tile
     */
	virtual CCSprite* tileAt(float x,float y);
	virtual CCSprite* tileAt(const CCPoint& tileCoordinate);
    
    /**
     * 删除tile
     */
	virtual void removeTileAt(float x,float y);
    virtual void removeTileAt(const CCPoint& pos);
 
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
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
    
    std::string m_sLayerName;
	CCSize m_tLayerSize;
    CCSize m_tMapTileSize;
	CCPoint m_tOffset;
	int m_iStartX;
	int m_iStartY;
    
    CCDictionary* m_pProperties;
       
    /**
      地图类型，斜视角，直角，六角。
      这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int m_uLayerOrientation;
    
    //! Layer supports opacity
    unsigned char       m_cOpacity;
    
    //! Only used when vertexZ is used
    int                 m_nVertexZvalue;
    bool                m_bUseAutomaticVertexZ;
        
    // used for retina display
    float               m_fContentScaleFactor;

};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_
