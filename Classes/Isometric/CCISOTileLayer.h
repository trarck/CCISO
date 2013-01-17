#ifndef ISO_CCISOTileLayer_H_
#define ISO_CCISOTileLayer_H_

#include "cocos2d.h"

NS_CC_BEGIN

class CCISOTileLayer : public CCNode {

public:
	
	CCISOTileLayer();
	~CCISOTileLayer(void);
	
    virtual bool init();

    /**
     * 初始化偏移
     */
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);

    /**
     * 获取tile
     */
	CCSprite* tileAt(float x,float y);
	CCSprite* tileAt(const CCPoint& tileCoordinate);
    
    /**
     * 获取tile gid
     */
    unsigned int  tileGIDAt(float x,float y);
    unsigned int  tileGIDAt(const CCPoint& tileCoordinate);
    
    /**
     * 设置tile gid
     */
    void setTileGID(unsigned int gid, float x,float y);
    void setTileGID(unsigned int gid, const CCPoint& tileCoordinate);

    /**
     * 删除tile
     */
	void removeTileAt(float x,float y);
    void removeTileAt(const CCPoint& pos);

    /**
     * 获取属性名称
     */
    CCString *propertyNamed(const char *propertyName);
    
    /**
     * 初始化显示tiles
     */
    void setupTiles();
    
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
    void setupTileSprite(CCSprite* sprite, CCPoint pos, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
    
    std::string m_sLayerName;
	CCSize m_tLayerSize;
    CCSize m_tTileSize;
	CCPoint m_tOffset;
	int m_iStartX;
	int m_iStartY;
    
    CCSprite* m_pReusedTile;
};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_
