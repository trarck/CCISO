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
    
    //get set 属性
    
	virtual void setLayerSize(const CCSize& tLayerSize);
	virtual CCSize getLayerSize();

    void setTileSize(const CCSize&  tileSize);
    void setTileSize(float width,float height);

	virtual void setOffset(const CCPoint& tOffset);
	virtual void setOffset(float x,float y);
    
	virtual CCPoint getOffset();
    
    inline const char* getLayerName(){ return m_sLayerName.c_str(); }
    inline void setLayerName(const char *layerName){ m_sLayerName = layerName; }
    
    virtual void setMapTileSize(const CCSize& tMapTileSize);
    virtual const CCSize& getMapTileSize();  
    
    virtual void setLayerOrientation(unsigned int uLayerOrientation);
    virtual unsigned int getLayerOrientation();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
//    virtual void setTileSet(CCISOTilesetInfo* pTileSet);
//    virtual CCISOTilesetInfo* getTileSet();
//    
//    virtual void setTiles(unsigned int* pTiles);
//    virtual unsigned int* getTiles();
//    
//    virtual void setTileSets(CCArray* pTileSets);
//    virtual CCArray* getTileSets();

protected:
    
    /**
     * 添加tile
     */
	CCSprite* appendTile(unsigned int gid, const CCPoint& pos);
    CCSprite* appendTile(unsigned int gid, float x,float y);
    
    /**
     * 插入tile
     */
    CCSprite* insertTile(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTile(unsigned int gid, float x,float y);
    
    /**
     * 更新tile
     */
    CCSprite* updateTile(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTile(unsigned int gid, float x,float y);
    
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
    
//    void setupTileSprite(CCSprite* sprite, CCPoint pos, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
         
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
protected:
    
    std::string m_sLayerName;
	CCSize m_tLayerSize;
    CCSize m_tTileSize;
	CCPoint m_tOffset;
	int m_iStartX;
	int m_iStartY;
    
   
    CCSize m_tMapTileSize;
    unsigned int* m_pTiles;
    CCISOTilesetInfo* m_pTileSet;
    unsigned int m_uLayerOrientation;
    CCDictionary* m_pProperties;
    //对于多个tileSet的支持。这样就不能使用batch node。所以最好一个layer使用一个tileSet
    CCArray* m_pTileSets;
    
    CCSpriteBatchNode* m_pSpriteBatchNode;
    
    
    //! TMX Layer supports opacity
    unsigned char        m_cOpacity;
    
    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;
    
    //! Only used when vertexZ is used
    int                    m_nVertexZvalue;
    bool                m_bUseAutomaticVertexZ;
    
    //! used for optimization
    CCSprite*           m_pReusedTile;
    ccCArray*           m_pAtlasIndexArray;
    
    // used for retina display
    float               m_fContentScaleFactor;

};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_
