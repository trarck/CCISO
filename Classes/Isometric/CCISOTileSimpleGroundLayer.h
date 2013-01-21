#ifndef ISO_CCISOTileSimpleGroundLayer_H_
#define ISO_CCISOTileSimpleGroundLayer_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"
#include "CCISOMapInfo.h"
#include "CCISOTilesetInfo.h"
#include "CCISOLayerInfo.h"

NS_CC_BEGIN

class CCISOTileSimpleGroundLayer : public CCISOTileLayer {

public:
	
	CCISOTileSimpleGroundLayer();
	~CCISOTileSimpleGroundLayer(void);
	
    virtual bool init();
    virtual bool init(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    /** creates a CCISOTileSimpleGroundLayer with an tileset info, a layer info and a map info
     @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE static CCISOTileSimpleGroundLayer * layerWithTilesetInfo(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    /** creates a CCISOTileSimpleGroundLayer with an tileset info, a layer info and a map info */
    static CCISOTileSimpleGroundLayer * create(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo);
    
    /** dealloc the map that contains the tile position from memory.
     Unless you want to know at runtime the tiles positions, you can safely call this method.
     If you are going to call layer->tileGIDAt() then, don't release the map
     */
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
     * 获取tile gid
     */
    unsigned int  tileGIDAt(float x,float y);
    unsigned int  tileGIDAt(const CCPoint& tileCoordinate);
    
    /**
     * 设置tile gid
     */
    virtual void setTileGID(unsigned int gid, float x,float y);
    virtual void setTileGID(unsigned int gid, const CCPoint& tileCoordinate);

    /**
     * 删除tile
     */
	virtual void removeTileAt(float x,float y);
    virtual void removeTileAt(const CCPoint& pos);

    
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    

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
    void parseInternalProperties();
    
    /**
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    
    virtual void setMapTileSize(const CCSize& tMapTileSize);
    virtual const CCSize& getMapTileSize();
    
    virtual void setTiles(unsigned int* pTiles);
    virtual unsigned int* getTiles();
    
    virtual void setTileSet(CCISOTilesetInfo* pTileSet);
    virtual CCISOTilesetInfo* getTileSet();
    
    virtual void setLayerOrientation(unsigned int uLayerOrientation);
    virtual unsigned int getLayerOrientation();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    virtual void setTileSets(CCArray* pTileSets);
    virtual CCArray* getTileSets();
    
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

#endif //ISO_CCISOTileSimpleGroundLayer_H_
