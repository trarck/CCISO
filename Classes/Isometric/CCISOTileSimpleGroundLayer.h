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
    unsigned int  tileGIDAt(float x,float y,ccTMXTileFlags* flags);
    unsigned int  tileGIDAt(const CCPoint& pos, ccTMXTileFlags* flags);
    
    /**
     * 设置tile gid
     */
    virtual void setTileGID(unsigned int gid, float x,float y);
    virtual void setTileGID(unsigned int gid, const CCPoint& tileCoordinate);
    void setTileGID(unsigned int gid, const CCPoint& tileCoordinate, ccTMXTileFlags flags);
    virtual void setTileGID(unsigned int gid, float x,float y, ccTMXTileFlags flags);
    /**
     * 删除tile
     */
	virtual void removeTileAt(float x,float y);
    virtual void removeTileAt(const CCPoint& pos);

    
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    virtual void removeChild(CCNode* child, bool cleanup);
    
    void setTiles(unsigned int* pTiles);
    unsigned int* getTiles();
    
    void setTileSet(CCISOTilesetInfo* pTileSet);
    CCISOTilesetInfo* getTileSet();
    
    void setTileSets(CCArray* pTileSets);
    CCArray* getTileSets();


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
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    
    CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);
    
    unsigned int atlasIndexForExistantZ(unsigned int z);
    unsigned int atlasIndexForNewZ(int z);
    
    void addQuadFromSprite(CCSprite *sprite, unsigned int index);
    void addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag);
    
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
