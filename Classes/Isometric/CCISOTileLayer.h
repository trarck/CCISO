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
     * 添加tile
     */
	void addTileAt(float x,float y);
	void addTileAt(const CCPoint& pos);

    /**
     * 获取tile
     */
	CCObject* getTileAt(float x,float y);
	CCObject* getTileAt(const CCPoint& pos);

    /**
     * 删除tile
     */
	void removeTileAt(float x,float y);
    void removeTileAt(const CCPoint& pos);

    /**
     * 更新前检查
     */
	bool beforeUpdateContent();
    
   
	virtual void setLayerSize(const CCSize& tLayerSize);
    
	virtual CCSize getLayerSize();
//	virtual void setContentSize(CCSize tContentSize);
//	virtual CCSize getContentSize();
	virtual void setName(const char* pName);
    
	virtual const char* getName();
    
    void setTileSize(const CCSize&  tileSize);
    void setTileSize(float width,float height);

	virtual void setOffset(const CCPoint& tOffset);
	virtual void setOffset(float x,float y);
    
	virtual CCPoint getOffset();


protected:
	CCSize m_tLayerSize;
//	CCSize m_tContentSize;
	const char* m_pName;
    CCSize m_tTileSize;
	CCPoint m_tOffset;
	int m_iStartX;
	int m_iStartY;
};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_
