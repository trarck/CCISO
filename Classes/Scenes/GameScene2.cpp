#include "cocos2d.h"
#include "GameScene.h"
#include "GameWorld.h"

USING_NS_CC;

NS_YH_BEGIN

GameScene::GameScene()
:m_pGameWorld(NULL)
{
    
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(m_pGameWorld);
}
//+(CGPoint) locationFromTouch:(UITouch *) touch
//{
//	CGPoint touchLocation=[touch locationInView:[touch view]];
//	return [[CCDirector sharedDirector] convertToGL:touchLocation];
//}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene* layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if(!CCLayer::init()){
        return false;
    }

    m_pGameWorld=new GameWorld();
    this.addChild(m_pGameWorld);
    m_pGameWorld.mapId=1;
    m_pGameWorld->release();

    //由GameWorld接收事件
    //UI层也由UI接收事件
//    m_bIsTouchEnabled=true;

	return self;
}

void  GameScene::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0,true);
}

bool  GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //GL coordinates
    CCPoint touchPoint = touch->getLocation(); 

	return true;
}
void  GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
		
}
void  GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

GameWorld*  GameScene::getGameWorld()
{
    return m_pGameWorld;
}

NS_YH_END