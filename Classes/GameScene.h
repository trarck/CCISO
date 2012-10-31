#ifndef GameScene_SCENE_H_
#define GameScene_SCENE_H_

#include "cocos2d.h"
#include "Player.h"

USING_NS_YH;

class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void menuRunCallback(CCObject* pSender);
    void menuStopCallback(CCObject* pSender);
    void menuMoveToCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
private:
    Player* m_player;
};

#endif // HELLOWORLD_SCENE_H__
