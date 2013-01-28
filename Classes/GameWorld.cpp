#include "SimpleAudioEngine.h"
#include "GameMessages.h"
#include "CCMessageManager.h"
#include "ISOCoordinateLayer.h"
#include "GameWorld.h"
#include "AttackComponent.h"
#include "AutoAttackComponent.h"
#include "Player.h"

#include "CCISOTileLayer.h"
#include "CCISOTileLayerDynamicComponent.h"
#include "CCISOTileMap.h"

USING_NS_CC;

NS_YH_BEGIN

enum{
	kLayerTagTestIsoLayer=1,
    kLayerTagTestIsoLayerDynamic
};
int mapItemGid=0;
const float MoveSmallDistance=3;

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
	CCLOG("GameWorld create");
}

GameWorld::~GameWorld()
{
	CCLOG("GameWorld destroy begin");
	CCLOG("player retain:%d",m_pPlayer->retainCount());
	CC_SAFE_RELEASE(m_pGameCamera);
	CC_SAFE_RELEASE(m_pAstar);
	CC_SAFE_RELEASE(m_pZIndex);
	//在创建的时候已经添加到自动释放池里了。
	//CC_SAFE_RELEASE(m_pBackground);
	//CC_SAFE_RELEASE(m_pIntermediate);
	//CC_SAFE_RELEASE(m_pForeground);
	CCLOG("player retain:%d",m_pPlayer->retainCount());
	CC_SAFE_RELEASE(m_pPlayer);
	CC_SAFE_RELEASE(m_pUnits);
    
	CCLOG("GameWorld destroy end");
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
	this->setTouchEnabled(true);
//    this->setScale(8);

	m_iMapColumn=20;
	m_iMapRow=20;

	//add coord line
	ISOCoordinateLayer* coordLayer=ISOCoordinateLayer::create();
	coordLayer->setMapWidth(m_iMapColumn);
	coordLayer->setMapHeight(m_iMapRow);
	this->addChild(coordLayer,100);
    
//    CCLayerColor* tempLayer=CCLayerColor::create(ccc4(0,0,255,255), 1000.0f, 1000.0f);
//    this->addChild(tempLayer);
    
    
    CCSprite* cellTile=CCSprite::create("grid13.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    
    CCPoint pos=isoGameToView2F(1, 1);
    pos.x-=0;
    CCLOG("init:%f,%f",pos.x,pos.y);
    cellTile->setPosition(pos);

    this->addChild(cellTile);

    cellTile=CCSprite::create("grid13.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    
    pos=isoGameToView2F(1, 0);
    pos.y+=0;
    CCLOG("init:%f,%f",pos.x,pos.y);
    cellTile->setPosition(pos);
    
    this->addChild(cellTile);
    
    cellTile=CCSprite::create("grid13.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    
    pos=isoGameToView2F(0, 1);
    pos.y+=0;
    CCLOG("init:%f,%f",pos.x,pos.y);
    cellTile->setPosition(pos);

    this->addChild(cellTile);
    
    cellTile=CCSprite::create("grid13.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    
    pos=isoGameToView2F(0, 0);
    pos.y+=0;
    CCLOG("init:%f,%f",pos.x,pos.y);
    cellTile->setPosition(pos);

    this->addChild(cellTile);
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
 //   float scaleX=screenSize.width/480;
	//float scaleY=screenSize.height/320;
	//this->setScale(scaleX>scaleY?scaleY:scaleX);

	//screenSize=CCSizeMake(480,320);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//                                        "CloseNormal.png",
//                                        "CloseSelected.png",
//                                        this,
//                                        menu_selector(GameWorld::menuCloseCallback) );
//    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );
//    
//    CCMenuItemLabel *pRunItem=CCMenuItemLabel::create(CCLabelTTF::create("run", "Arial", 12),
//                                                      this, 
//                                                      menu_selector(GameWorld::menuRunCallback));
//    pRunItem->setPosition(ccp(screenSize.width-60,20));
//    
//    CCMenuItemLabel *pStopItem=CCMenuItemLabel::create(CCLabelTTF::create("stop", "Arial", 12),
//                                                      this, 
//                                                      menu_selector(GameWorld::menuStopCallback));
//    pStopItem->setPosition(ccp(screenSize.width-90,20));
//    
//    CCMenuItemLabel *pMoveToItem=CCMenuItemLabel::create(CCLabelTTF::create("moveTo", "Arial", 12),
//                                                       this, 
//                                                       menu_selector(GameWorld::menuMoveToCallback));
//    pMoveToItem->setPosition(ccp(screenSize.width-120,20));
//    
//    // create menu, it's an autorelease object
//    CCMenu* pMenu = CCMenu::create(pCloseItem,pRunItem,pStopItem,pMoveToItem, NULL);
//    pMenu->setPosition( CCPointZero );
//    this->addChild(pMenu, 1);

    
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
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//m_pUnits=new CCArray(10);

	m_pGameCamera=new GameCamera();
	m_pGameCamera->init();
	m_pGameCamera->setGameWorld(this);
    m_pGameCamera->moveTo(-screenSize.width/2, 0);
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
	m_pAstar->setCheckBarrierHandle(check_barrier_selector(GameWorld::isWorkable),this);
	
	//CC_SAFE_RELEASE(m_pZIndex);
	//m_pZIndex=new CCZIndex();
	//m_pZIndex->init(m_pIntermediate);
	//m_pZIndex->start();
	//m_pZIndex->release();
}

/**
 * 初始化地图层
 */
void GameWorld::setupGameWorlds()
{
//    CCISOTileLayer* testLayer=new CCISOTileLayer();
//    testLayer->init();
//    testLayer->setTileSize(TileWidth,TileHeight);
//    this->addChild(testLayer,0,kLayerTagTestIsoLayer);
//    testLayer->visitTileShowable();
    
    CCISOTileMap* testMap=new CCISOTileMap();
    testMap->init();
    this->addChild(testMap);
    
    CCISOTileLayerDynamicComponent* testLayer=new CCISOTileLayerDynamicComponent();
    testLayer->init();
    testLayer->setMapTileSize(TileWidth,TileHeight);
    
    testLayer->setupComponents(2,ccp(-192,0));//ccp(-160,234)
//    testLayer->visitTileShowable();
    //testLayer->scroll(ccp(-160,234));
    this->addChild(testLayer,0,kLayerTagTestIsoLayerDynamic);
    
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
	CCLOG("player retain:%d",m_pPlayer->retainCount());
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
	m_pPlayer->setCoordinateAndTranslate(coord);
	m_pPlayer->setGameWorld(this);
	m_pPlayer->setupComponents();
	addInterMediateDynamicEntity(m_pPlayer);
	CCLOG("m_pPlayer count:%d",m_pPlayer->retainCount());
}


void GameWorld::addTeammateAtCoord(CCPoint coord)
{
	Player* player=new Player();
	player->init(3);
	player->setCoordinateAndTranslate(coord);
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
	CCLOG("m_pPlayer1 count:%d",m_pPlayer->retainCount());
    this->removeAllChildrenWithCleanup(true);
	CCLOG("m_pPlayer2 count:%d",m_pPlayer->retainCount());
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
    
    CCPoint* direction=new CCPoint(1,1);
	direction->autorelease();
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION, NULL, m_pPlayer,direction);

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
    CCPoint to=isoViewToGame2F(screenSize.width/2+50,screenSize.height/2+50);
	CCPoint from=m_pPlayer->getCoordinate();
    
	CCArray* paths=searchPathsFrom(from,to);
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
	paths->release();
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
	
	m_bIsTouchMoved=false;
	m_startTouchLocation=touchPoint;
	m_startPoint=this->getPosition();
	m_lastTouchLocation=touchPoint;

	CCPoint mapCoord=isoViewToGamePoint(m_pGameCamera->getLocationInWorld(touchPoint));
	CCLOG("touch began view cood:%f,%f,map:%f,%f",touchPoint.x,touchPoint.y,mapCoord.x,mapCoord.y);
	return true;
}
void  GameWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!m_bIsTouchMoved){
		 CCPoint touchPoint = pTouch->getLocation();
		 touchPoint=m_pGameCamera->getLocationInWorld(touchPoint);
		 CCPoint to=isoViewToGamePoint(touchPoint);
		 //如果player正在移动，则此时取到的坐标和最终停下来的不一致。
		 CCPoint from=m_pPlayer->getCoordinate();
    
		 CCArray* paths=searchPathsFrom(from,to);
		 if(paths){
			 CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_PATH, NULL, m_pPlayer,paths);
			 paths->release();
		 }
	}else{
		//CCISOTileLayer* tileLayer=(CCISOTileLayer*)this->getChildByTag(kLayerTagTestIsoLayer);
		//if(tileLayer->isCellChange()){
		//	CCLOG("do visit");
		//	tileLayer->removeAllChildrenWithCleanup(true);
		//	tileLayer->visitTileShowable();
		//}
	}
}
void  GameWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	float dx=touchPoint.x-m_startTouchLocation.x;
	float dy=touchPoint.y-m_startTouchLocation.y;
	if(abs(dx)>MoveSmallDistance || abs(dy)>MoveSmallDistance){
		m_bIsTouchMoved=true;
		m_pGameCamera->moveOpposite(touchPoint.x-m_lastTouchLocation.x,touchPoint.y-m_lastTouchLocation.y);
		
//		CCISOTileLayer* tileLayer=(CCISOTileLayer*)this->getChildByTag(kLayerTagTestIsoLayer);
//		CCPoint pos=tileLayer->getOffset();
//		pos.x+=touchPoint.x-m_lastTouchLocation.x;
//		pos.y+=touchPoint.y-m_lastTouchLocation.y;
//		tileLayer->scroll(pos);
        
        
		/*if(tileLayer->isCellChange()){
			CCLOG("do visit");
			tileLayer->removeAllChildrenWithCleanup(true);
			tileLayer->visitTileShowable();
		}*/
		//tileLayer->removeAllChildrenWithCleanup(true);
		//tileLayer->visitTileShowable();

		m_lastTouchLocation=touchPoint;
	}
}

void GameWorld::updateMapPosition(const CCPoint& position)
{
    CCISOTileLayerDynamicComponent* tileLayer=(CCISOTileLayerDynamicComponent*)this->getChildByTag(kLayerTagTestIsoLayerDynamic);
    tileLayer->scroll(position);
}

CCPoint GameWorld::toGameCoordinate(const CCPoint& position)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(position));
}

CCPoint GameWorld::toGameCoordinate(float x,float y)
{
    return isoViewToGamePoint(m_pGameCamera->getLocationInWorld(ccp(x,y)));
}

void GameWorld::updateMapPosition(float x,float y)
{
    updateMapPosition(ccp(x,y));
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

bool GameWorld::isWorkable(int x ,int y)
{
    return true;
}
NS_YH_END