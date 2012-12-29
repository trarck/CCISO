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
    
    m_pGameWorld=new GameWorld();
	m_pGameWorld->init();
    this->addChild(m_pGameWorld);
    //m_pGameWorld.mapId=1;
    m_pGameWorld->release();

    return true;
}

GameWorld*  GameScene::getGameWorld()
{
    return m_pGameWorld;
}


NS_YH_END