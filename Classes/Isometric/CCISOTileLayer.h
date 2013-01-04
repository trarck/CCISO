#ifndef ISO_CCISOTileLayer_H_
#define ISO_CCISOTileLayer_H_

#include "cocos2d.h"

NS_CC_BEGIN


class CCISOTileLayer : public CCNode {

public:
	
	CCISOTileLayer();
	~CCISOTileLayer(void);
	
    bool init();

	void addTileAt(float x,float y);
	void addTileAt(const CCPoint& pos);

	CCObject* getTileAt(float x,float y);
	CCObject* getTileAt(const CCPoint& pos);

	void removeTileAt(float x,float y);
    void removeTileAt(const CCPoint& pos);

	void visitShowTile();

	virtual void setLayerSize(CCSize tLayerSize);
	virtual CCSize getLayerSize();
//	virtual void setContentSize(CCSize tContentSize);
//	virtual CCSize getContentSize();
	virtual void setName(const char* pName);
	virtual const char* getName();

protected:
	CCSize m_tLayerSize;
//	CCSize m_tContentSize;
	const char* m_pName;

};



NS_CC_END

#endif //ISO_CCISOTileLayer_H_