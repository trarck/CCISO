#ifndef LAYERS_ISOCOORDINATELAYER_H_
#define LAYERS_ISOCOORDINATELAYER_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "Player.h"

USING_NS_CC;

NS_YH_BEGIN

class ISOCoordinateLayer: public CCLayer
{
public:
	ISOCoordinateLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(ISOCoordinateLayer);
	
	virtual void draw();

	void showCoordinate(bool isShow);

	virtual void setMapWidth(int iMapWidth);
	virtual int getMapWidth();
	virtual void setMapHeight(int iMapHeight);
	virtual int getMapHeight();
private:
	int m_iMapWidth;
	int m_iMapHeight;
	bool m_bIsShow;
};

NS_YH_END

#endif // LAYERS_ISOCOORDINATELAYER_H_