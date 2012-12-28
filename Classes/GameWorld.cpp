#include "GameWorld.h"

USING_NS_CC;

NS_YH_BEGIN
// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

  
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height - 50 + origin.y));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "GameWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("GameWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}
NS_YH_END