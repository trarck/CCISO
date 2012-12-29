#include "GameWorld.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "GameMessages.h"
#include "CCMessageManager.h"
#include "AttackComponent.h"

#include "AutoAttackComponent.h"


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
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );
    
    CCMenuItemLabel *pRunItem=CCMenuItemLabel::create(CCLabelTTF::create("run", "Arial", 12),
                                                      this, 
                                                      menu_selector(GameWorld::menuRunCallback));
    pRunItem->setPosition(ccp(screenSize.width-60,20));
    
    CCMenuItemLabel *pStopItem=CCMenuItemLabel::create(CCLabelTTF::create("stop", "Arial", 12),
                                                      this, 
                                                      menu_selector(GameWorld::menuStopCallback));
    pStopItem->setPosition(ccp(screenSize.width-90,20));
    
    CCMenuItemLabel *pMoveToItem=CCMenuItemLabel::create(CCLabelTTF::create("moveTo", "Arial", 12),
                                                       this, 
                                                       menu_selector(GameWorld::menuMoveToCallback));
    pMoveToItem->setPosition(ccp(screenSize.width-120,20));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem,pRunItem,pStopItem,pMoveToItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...
    Player* player=new Player();
    CCLOG("player count=%d",player->retainCount());
    player->init();
    CCLOG("player count=%d",player->retainCount());
    player->setupComponents();
    CCLOG("player count=%d",player->retainCount());
    
    player->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    
//    this->addChild(player->view());
    this->addChild(player);
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    CCLOG("set begin action");
    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, player,data);
    CCLOG("set begin action after");
    
    
    Unit* target=new Unit();
    target->setHealth(10);
    
//    player->sendMessage(SET_ATTACK_TARGET, NULL, target);
    
    CCLOG("send attack message");
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
    
    for(int i=0;i<1;i++){
        CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player);
    }
    
//    AttackComponent* attackComponent=(AttackComponent*)player->getComponent("AttackComponent");
    
        
    target->release();
    player->release();
    
    m_player=player;
    
//    player->removeFromParentAndCleanup(true);

    
//    CCLOG("attackComponent count=%d",attackComponent->retainCount());
}

void GameWorld::menuCloseCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameWorld::menuRunCallback(CCObject* pSender)
{
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("move"), "name");
//    data->setObject(CCInteger::create(3), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_player,data);
//    CCLOG("set begin action after");
    
    CCInteger* degree=CCInteger::create(45);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION, NULL, m_player,degree);

}

void GameWorld::menuStopCallback(CCObject* pSender)
{
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_player,data);
//    CCLOG("set begin action after");

    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION_STOP, NULL, m_player);
}

void GameWorld::menuMoveToCallback(CCObject* pSender)
{
   
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    CCPoint to=ccp(screenSize.width/2+50,screenSize.height/2+50);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, m_player,&to);
    
}

NS_YH_END