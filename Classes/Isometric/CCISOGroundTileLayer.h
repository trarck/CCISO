#ifndef ISO_CCISOGroundTileLayer_H_
#define ISO_CCISOGroundTileLayer_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"
#include "CCISOInfos.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

struct _ccCArray;

class CCISOGroundTileLayer : public CCISOTileLayer {

public:
	
	CCISOGroundTileLayer();
    
	~CCISOGroundTileLayer(void);
	
//    virtual bool init(CCISOTileMap *pMap);

    /** dealloc the map that contains the tile position from memory.
     Unless you want to know at runtime the tiles positions, you can safely call this method.
     If you are going to call layer->tileGIDAt() then, don't release the map
     */
    virtual void releaseLayer();

    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    /**
     * 获取tile
     */
    
	virtual CCSprite* tileSpriteAt(const CCPoint& pos);
    
    /**
     * 删除tile
     */
    virtual void removeSpriteTileAt(const CCPoint& pos);

public:
        
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
    
    CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);
    
protected:
    
    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;

};



NS_CC_END

#endif //ISO_CCISOGroundTileLayer_H_
