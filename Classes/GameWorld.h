#ifndef CCISO_GAMEWORLD_H_
#define CCISO_GAMEWORLD_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "Player.h"

USING_NS_CC;

NS_YH_BEGIN

class GameWorld: public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);

	 // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 
private:
	Player* m_player;
};

NS_YH_END

#endif // CCISO_GAMEWORLD_H_
