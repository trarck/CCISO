#include "GameScene.h"

USING_NS_CC;

NS_YH_BEGIN

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );
    
        // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


    m_pGameWorld=new GameWorld();
	m_pGameWorld->init();
	m_pGameWorld->setup();
    this->addChild(m_pGameWorld);
    //m_pGameWorld.mapId=1;
    m_pGameWorld->release();
    
    m_pMapCoordLabel=NULL;
    m_bDisplayStats=true;
    
    this->createStatsLabel();

    return true;
}

GameWorld*  GameScene::getGameWorld()
{
    return m_pGameWorld;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::createStatsLabel()
{
    
    CCSize screenSize=CCDirector::sharedDirector()->getWinSize();
    
    int fontSize = 0;
    if (screenSize.width > screenSize.height)
    {
        fontSize = (int)(screenSize.height / 320.0f * 24);
    }
    else
    {
        fontSize = (int)(screenSize.width / 320.0f * 24);
    }
    
    
    m_pMapCoordLabel = CCLabelTTF::create("0000.0,0000.0", "Arial", fontSize);
   
    
    //CCTexture2D::setDefaultAlphaPixelFormat(currentFormat);
    
    
    CCSize contentSize = m_pMapCoordLabel->getContentSize();
    m_pMapCoordLabel->setPosition(ccpAdd(ccp(contentSize.width, contentSize.height*7/2), CCDirector::sharedDirector()->getVisibleOrigin()));
    
    this->addChild(m_pMapCoordLabel);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameScene::updateState), this, 1.0f, false);
}

void GameScene::updateState(float delta)
{
    if (m_bDisplayStats)
    {
        if (m_pMapCoordLabel)
        {
            char* coordBuff=new char[50];
            CCPoint mapCoord=m_pGameWorld->toGameCoordinate(0,0);
            CCLOG("%f,%f",mapCoord.x,mapCoord.y);
            sprintf(coordBuff, "%.1f,%.1f", mapCoord.x,mapCoord.y);
            m_pMapCoordLabel->setString(coordBuff);
            
            delete coordBuff;
            
        }
    }

}



NS_YH_END