//
//  AstarNode.h
//  isometric
//
#ifndef ISO_CCISOTileMap_H_
#define ISO_CCISOTileMap_H_

#include "cocos2d.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN


class CCISOTileMap : public CCNode {

public:
	
	CCISOTileMap();
	~CCISOTileMap(void);
	
    bool init();

	CCISOTileLayer* getLayerByName(const char* layerName);
    
	virtual void setMapSize(CCSize tMapSize);
	virtual CCSize getMapSize();
	//virtual void setContentSize(CCSize tContentSize);
	//virtual CCSize getContentSize();
	virtual void setName(const char* pName);
	virtual const char* getName();
protected:
	CCSize m_tMapSize;
	CCSize m_tContentSize;
	const char* m_pName;
};



NS_CC_END

#endif //ISO_CCIOSTileMap_H_
