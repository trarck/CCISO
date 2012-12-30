#include "GameWorld.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "GameMessages.h"
#include "CCMessageManager.h"
#include "AttackComponent.h"

#include "AutoAttackComponent.h"

#include "ISOCoordinateLayer.h"

USING_NS_CC;

NS_YH_BEGIN

int mapItemGid=0;

GameWorld::GameWorld()
:m_iMapColumn(0)
,m_iMapRow(0)
,m_iMapId(0)
,m_pBackground(NULL)
,m_pIntermediate(NULL)
,m_pForeground(NULL)
,m_pAstar(NULL)
,m_pZIndex(NULL)
,m_pPlayer(NULL)
,m_bIsTouchMoved(true)
,m_pUnits(NULL)
{

}

GameWorld::~GameWorld()
{

}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	m_bIsTouchEnabled=true;

	m_iMapColumn=20;
	m_iMapRow=20;

	//add coord line
	ISOCoordinateLayer* coordLayer=ISOCoordinateLayer::create();
	coordLayer->setMapWidth(m_iMapColumn);
	coordLayer->setMapHeight(m_iMapRow);
	this->addChild(coordLayer);
    
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
//    Player* player=new Player();
//    CCLOG("player count=%d",player->retainCount());
//    player->init();
//    CCLOG("player count=%d",player->retainCount());
//    player->setupComponents();
//    CCLOG("player count=%d",player->retainCount());
//    
//    player->setPosition(ccp(screenSize.width/2, screenSize.height/2));
//    
////    this->addChild(player->view());
//    this->addChild(player);
//    
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, player,data);
//    CCLOG("set begin action after");
//    
//    
//    Unit* target=new Unit();
//    target->setHealth(10);
//    
////    player->sendMessage(SET_ATTACK_TARGET, NULL, target);
//    
//    CCLOG("send attack message");
//    
//    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
//    
//    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
//    
//    for(int i=0;i<1;i++){
//        CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player);
//    }
//    
////    AttackComponent* attackComponent=(AttackComponent*)player->getComponent("AttackComponent");
//    
//        
//    target->release();
//    player->release();
//    
//    m_pPlayer=player;
    
	return true;
}

bool GameWorld::init(int mapId)
{
	init();
	m_iMapId=mapId;
	return true;
}
void GameWorld::setup()
{
	m_pUnits=new CCArray(10);

	//base
	setupGameWorlds();
	setupUtil();
	//objects
	loadBackground();
	loadInterMediate();
	
	//setupNetWork();
}

void GameWorld::loadMapData()
{
	
}

/**
 * 初始化一些工具方法
 * 寻路，坐标转换
 */
void GameWorld::setupUtil()
{
	//astar search
	CC_SAFE_RELEASE(m_pAstar);
	m_pAstar=new CCAstar();
	m_pAstar->init();
	m_pAstar->setBounding(0,0,m_iMapColumn,m_iMapRow);
	
	CC_SAFE_RELEASE(m_pZIndex);
	m_pZIndex=new CCZIndex();
	m_pZIndex->init(m_pIntermediate);
	m_pZIndex->start();
	m_pZIndex->release();
}

/**
 * 初始化地图层
 */
void GameWorld::setupGameWorlds()
{
	m_pBackground=CCLayer::create();
	m_pBackground->setPosition(ccp(0,0));
	this->addChild(m_pBackground,Background_ZOrder);
		
	m_pIntermediate=CCLayer::create();
	m_pIntermediate->setPosition(ccp(0,0));
	this->addChild(m_pIntermediate,Intermediate_ZOrder);
	
	m_pForeground=CCLayer::create();
	m_pForeground->setPosition(ccp(0,0));
	this->addChild(m_pForeground,Foreground_ZOrder);
	
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	////moveable size
	//moveableBoundingMax_.x=TileWidth*mapData_.row/2;
	//moveableBoundingMax_.y=0;
	//moveableBoundingMin_.x=screenSize.width-TileWidth*mapData_.column/2;
	//moveableBoundingMin_.y=screenSize.height-TileHeight*(mapData_.row+mapData_.column)/2;
	
	//this->setPosition(ccp(screenSize.width/2,0));
}

//void GameWorld::setupNetWork()
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->connectServer("10.10.49.217",8124);
//	//gameClient->login();
//	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameWorld::say),this,10,false);
//}
//
//void GameWorld::say(float delta)
//{
//	//TcpClient* gameClient=TcpClient::sharedTcpClient();
//	//gameClient->say("hello every one");
//}

/**
 * 输入地图背景层
 */
void GameWorld::loadBackground()
{	

	CCLOG("GameWorld loadBackground");
	
}

/**
 * 载入游戏内容
 *
 */
void GameWorld::loadInterMediate()
{
	addPlayerAtCoord(ccp(5,0));	
	m_pPlayer->setAnchorPoint(ccp(0.5,0));
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_pPlayer,data);
}

void GameWorld::addInterMediateDynamicEntity(Unit* entity)
{
	CCPoint coord=entity->getCoordinate();
	int z=-(int)(coord.x+coord.y);
	m_pIntermediate->addChild(entity,z,mapItemGid++);
}

void GameWorld::addInterMediateStaticEntity(WorldEntity* entity)
{
	CCPoint coord=entity->getCoordinate();
	int z=-(int)(coord.x+coord.y);
	m_pIntermediate->addChild(entity,z,mapItemGid++);
}

void GameWorld::removeInterMediateDynamicEntity(Unit* entity)
{
	m_pIntermediate->removeChild(entity,false);
}

void GameWorld::removeInterMediateStaticEntity(WorldEntity* entity) 
{
	m_pIntermediate->removeChild(entity,false);
}

/**
 * 增加一个主角
 * @param {CCPoint} coord 地图坐标
 */
void GameWorld::addPlayerAtCoord(CCPoint coord)
{
	m_pPlayer=new Player();
	m_pPlayer->init(2);
	m_pPlayer->setCoordinate(coord);
	m_pPlayer->setGameWorld(this);
	m_pPlayer->setupComponents();
	addInterMediateDynamicEntity(m_pPlayer);
}


void GameWorld::addTeammateAtCoord(CCPoint coord)
{
	Player* player=new Player();
	player->init(3);
	player->setCoordinate(coord);
	player->setGameWorld(this);
	player->setupComponents();
	addInterMediateDynamicEntity(player);
	player->release();
}

void GameWorld::removeTeammate(Player* player)
{
	removeInterMediateDynamicEntity(player);
}

/**
 * 移动主角
 * @param {CCPoint} location 视图坐标
 */
void GameWorld::movePlayerToViewLocation(CCPoint location)
{
	moveViewEntity(m_pPlayer,location);
}

void GameWorld::moveViewEntity(Unit* entity,CCPoint location)
{
	CCPoint coord=isoViewToGamePoint(location);
	moveEntity(entity,coord);
}

void GameWorld::moveEntity(Unit* entity,CCPoint coord)
{
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, entity,&coord);
}

/**
 * 对寻路算法的封装
 */
CCArray* GameWorld::searchPathsFrom(int fromX ,int fromY ,int toX ,int toY)
{
	m_pAstar->reset();
	m_pAstar->setStart(fromX ,fromY);
	m_pAstar->setEnd(toX ,toY);
	
	return m_pAstar->search()?m_pAstar->getPathWithEnd():NULL;
}

/**
 * 对寻路算法的封装
 * 返回的数组要手动释放
 */
CCArray* GameWorld::searchPathsFrom(CCPoint from ,CCPoint to )
{
	m_pAstar->reset();
	m_pAstar->setStart((int)from.x ,(int) from.y);
	m_pAstar->setEnd((int)to.x ,(int) to.y);
	bool result=m_pAstar->search();
	return result?m_pAstar->getPathWithEnd():NULL;
}

/**
 * 地图格子转成视图坐标(视图坐标不同于屏幕坐标)
 * 返回的数组要手动释放
 */
CCArray* GameWorld::mapPathsToViewPaths(CCArray* paths)
{
	if (paths) {
		CCArray *newPaths=new CCArray(paths->count());
		CCPoint* newp=NULL;
		CCPoint* it=NULL;
		CCObject* pObj=NULL;
		CCARRAY_FOREACH(paths,pObj){
			it=(CCPoint*)pObj;
			newp=isoGameToView2FP(it->x,it->y);
			newPaths->addObject(newp);
		}
		return newPaths;
	}else {
		return NULL;
	}
}

void GameWorld::showGameOver()
{
	//CCDirector::sharedDirector()->replaceScene(GameOverScene::scene);
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
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_pPlayer,data);
//    CCLOG("set begin action after");
    
    CCInteger* degree=CCInteger::create(45);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION, NULL, m_pPlayer,degree);

}

void GameWorld::menuStopCallback(CCObject* pSender)
{
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_pPlayer,data);
//    CCLOG("set begin action after");

    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION_STOP, NULL, m_pPlayer);
}

void GameWorld::menuMoveToCallback(CCObject* pSender)
{
   
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    CCPoint to=ccp(screenSize.width/2+50,screenSize.height/2+50);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, m_pPlayer,&to);
    
}

void  GameWorld::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool  GameWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //GL coordinates
    CCPoint touchPoint = pTouch->getLocation(); 
	CCPoint mapCoord=isoViewToGame2F(touchPoint.x,touchPoint.y);
	CCLOG("touch began view cood:%f,%f,map:%f,%f",touchPoint.x,touchPoint.y,mapCoord.x,mapCoord.y);
	return true;
}
void  GameWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	 CCPoint touchPoint = pTouch->getLocation();
    
     CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, m_pPlayer,&touchPoint);
}
void  GameWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}


void GameWorld::setMapColumn(int iMapColumn)
{
    m_iMapColumn = iMapColumn;
}

int GameWorld::getMapColumn()
{
    return m_iMapColumn;
}

void GameWorld::setMapRow(int iMapRow)
{
    m_iMapRow = iMapRow;
}

int GameWorld::getMapRow()
{
    return m_iMapRow;
}

void GameWorld::setMapId(int iMapId)
{
    m_iMapId = iMapId;
}

int GameWorld::getMapId()
{
    return m_iMapId;
}

void GameWorld::setBackground(CCLayer* pBackground)
{
    CC_SAFE_RETAIN(pBackground);
    CC_SAFE_RELEASE(m_pBackground);
    m_pBackground = pBackground;
}

CCLayer* GameWorld::getBackground()
{
    return m_pBackground;
}

void GameWorld::setIntermediate(CCLayer* pIntermediate)
{
    CC_SAFE_RETAIN(pIntermediate);
    CC_SAFE_RELEASE(m_pIntermediate);
    m_pIntermediate = pIntermediate;
}

CCLayer* GameWorld::getIntermediate()
{
    return m_pIntermediate;
}

void GameWorld::setForeground(CCLayer* pForeground)
{
    CC_SAFE_RETAIN(pForeground);
    CC_SAFE_RELEASE(m_pForeground);
    m_pForeground = pForeground;
}

CCLayer* GameWorld::getForeground()
{
    return m_pForeground;
}


NS_YH_END