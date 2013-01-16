#ifndef ISO_CCISOTileLayer_H_
#define ISO_CCISOTileLayer_H_

#include "cocos2d.h"

NS_CC_BEGIN
static const CCSize testSize=CCSizeMake(480,320);

class CCISOTileLayer : public CCNode {

public:
	
	CCISOTileLayer();
	~CCISOTileLayer(void);
	
    virtual bool init();

	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);

	void addTileAt(float x,float y);
	void addTileAt(const CCPoint& pos);

	CCObject* getTileAt(float x,float y);
	CCObject* getTileAt(const CCPoint& pos);

	void removeTileAt(float x,float y);
    void removeTileAt(const CCPoint& pos);

	bool beforeUpdateContent();
	void doUpdateContent();
    void doUpdateContent2();

	bool isCellChange();
    void visitTileShowable();
    void visitTileShowable2();
    
    virtual void draw();
    
    
	virtual void setLayerSize(const CCSize& tLayerSize);
	virtual CCSize getLayerSize();
//	virtual void setContentSize(CCSize tContentSize);
//	virtual CCSize getContentSize();
	virtual void setName(const char* pName);
	virtual const char* getName();
    
    void setTileSize(const CCSize&  tileSize);
    void setTileSize(float width,float height);

    //只作判断使用，不改变显示位置
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
	virtual void setOffset(const CCPoint& tOffset);
	virtual void setOffset(float x,float y);
	virtual CCPoint getOffset();


protected:
	CCSize m_tLayerSize;
//	CCSize m_tContentSize;
	const char* m_pName;
    CCSize m_tTileSize;
	CCPoint m_tOffset;
	CCPoint m_tLastStartPoint;
	int m_iStartX;
	int m_iStartY;
};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_
