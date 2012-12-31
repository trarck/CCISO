/**
 * 现在是按照位置来判断结束于否。
 * 可以考虑按时间来判断。
 */
#include "CCMessageManager.h"
#include "GridMoveComponent.h"
#include "GameEntity.h"
#include "WorldEntity.h"
#include "GameMessages.h"

#define AXIS_VECTOR 1
//sqrt(2)
#define BEVEL_VECTOR 1.414213562373
#define BEVEL_VECTOR_HALF 0.70710678
#define MOVIE_TIME_UNIT 1000

USING_NS_CC;

NS_YH_BEGIN

static int directionMapping[3][3]={
	{4,1,5},
	{0,-1,2},
	{7,3,6}
};

static float MoveDurationMap[3][3]={
	{BEVEL_VECTOR*MOVIE_TIME_UNIT,AXIS_VECTOR*MOVIE_TIME_UNIT,BEVEL_VECTOR*MOVIE_TIME_UNIT},
	{AXIS_VECTOR*MOVIE_TIME_UNIT,0,AXIS_VECTOR*MOVIE_TIME_UNIT},
	{BEVEL_VECTOR*MOVIE_TIME_UNIT,AXIS_VECTOR*MOVIE_TIME_UNIT,BEVEL_VECTOR*MOVIE_TIME_UNIT}
};

GridMoveComponent::GridMoveComponent()
:m_speed(0.0f)
,m_direction(0.0f)
,m_directionX(0)
,m_directionY(0)
,m_moving(false)
,m_to(ccp(0.0f, 0.0f))
,m_hasEndPosition(false)
,m_isDirectionDirty(true)
,m_pCurrentPaths(NULL)
,m_pNextPaths(NULL)
{
    CCLOG("GridMoveComponent create");
}

GridMoveComponent::~GridMoveComponent()
{
    CCLOG("GridMoveComponent destroy");
	CC_SAFE_RELEASE(m_pCurrentPaths);
	CC_SAFE_RELEASE(m_pNextPaths);
}

bool GridMoveComponent::init()
{
	if(Component::init()){
		m_moveState=MoveStop;      
	}
    return true;
	
}

bool GridMoveComponent::init(float speed)
{
	if (init()) {
		m_speed=speed;
	}
	return true;
}

void GridMoveComponent::handleMessage(CCMessage *message)
{
    CCLOG("GridMoveComponent::handleMessage");
    CCLOG("get message %d",message->getType());
    
 
	switch(message->getType()){
            
		case MOVE_DIRECTION :
        {
            CCInteger* integer=(CCInteger*)message->getData();
            moveWithDirection(kmDegreesToRadians(integer->getValue()));
            break;
        }
        case MOVE_DIRECTION_STOP:
            stopMove();
            break;
        case MOVE_TO:
        {
            CCPoint to=*(CCPoint*)message->getData();
            //moveTo(to);
            break;
        }
	}
}

bool GridMoveComponent::registerMessages()
{
    CCLOG("GridMoveComponent::registerMessages");
    
    SEL_MessageHandler handle=message_selector(GridMoveComponent::handleMessage);
    
    CCMessageManager::defaultManager()->registerReceiver(m_owner, handle, MOVE_DIRECTION, NULL,this); 
    CCMessageManager::defaultManager()->registerReceiver(m_owner, handle, MOVE_DIRECTION_STOP, NULL,this);
    CCMessageManager::defaultManager()->registerReceiver(m_owner, handle, MOVE_TO, NULL,this);
    
    return true;
}

bool GridMoveComponent::isMoving()
{
    return m_moving;
}

MoveState GridMoveComponent::getMoveState()
{
    return m_moveState;
}

CCPoint GridMoveComponent::movingCoordinate()
{
	CCPoint coord;
//	if (m_moveState==MoveStart) {
//		coord=m_to;
//	}else {
//		coord.x=m_owner.mx;
//		coord.y=m_owner.my;
//	}
	return coord;
}



/**
 * 移动之前进行检查
 */

bool GridMoveComponent::beforeMove()
{
	return true;
}

/**
 * 开始移动
 * 设置移动动画的定时器
 */
void GridMoveComponent::startMove()
{
    CCLOG("startMove");
	m_moveState=MoveStart;
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->scheduleSelector(m_update,this, 0, false);
    doMoveStart();
}

/**
 * 停止移动
 * 取消移动动画的定时器
 */
void GridMoveComponent::stopMove()
{
	if(m_moveState==MoveStart){
		m_moveState=MoveWillStop;
	}else {
		CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->unscheduleSelector(m_update, this);
		m_moveState=MoveStop;
		//NSLog(@"stop entity move schedule:update");
		doMoveStop();
	}
}

#pragma mark -
#pragma mark 按方向移动

/**
 * 按指定方向偏移量,这里不考虑速度叠加.
 */
void GridMoveComponent::moveWithDirection(float directionX ,float directionY)
{
    m_update=schedule_selector(GridMoveComponent::updateDirection);

	if (m_moveState==MoveStop) {
		setDirection(directionX,directionY);
		prepareDirection(directionX, directionY);
    
		if(checkMoveable()){
			startMove();
		}
	}else {
		continueMoveWithDirection(directionX,directionY);
	}
}

void GridMoveComponent::moveWithDirection(CCPoint direction)
{
    moveWithDirection(direction.x, direction.y);
}
/**
 * 断续指定方向移动
 */
void GridMoveComponent::continueMoveWithDirection(float directionX ,float directionY)
{
	setNextDirection(directionX,directionY);
	m_moveState=MoveContinue;
}

void GridMoveComponent::continueMoveWithDirection(CCPoint direction)
{
	continueMoveWithDirection(direction.x, direction.y);
}

void GridMoveComponent::prepareDirection(float directionX,float directionY)
{
	calcMoveDuration(directionX,directionY);
	calcSpeedVector(directionX,directionY);

}

void GridMoveComponent::calcMoveDuration(float directionX,float directionY)
{
	//计算本次移动所需要的时间
	//+0.5 四舍五入的修正
	//+1.由于-1=<directionX<=1,偏移一个1，正好0<=directionX+1<=2。起点和数组下标吻合
	int i=floor(directionX+0.5)+1;
	int j=floor(directionY+0.5)+1;
	CCAssert(i>=0 && i<=2,"prepareDirection error the direction out of range");
	CCAssert(j>=0 && j<=2,"prepareDirection error the direction out of range");
	float m_movingDuration=MoveDurationMap[i][j];

	//float absDirX=abs(directionX);
	//float absDirY=abs(directionY);

	//if((absDirX<FLOAT_ZERO_FLAG&&absDirY>FLOAT_ZERO_FLAG)||(absDirX>FLOAT_ZERO_FLAG&&absDirY<FLOAT_ZERO_FLAG)){
	//	m_movingDuration=AXIS_VECTOR*1000;//毫秒
	//}else{
	//	if(abs(directionX)>FLOAT_ZERO_FLAG&&abs(directionY)>FLOAT_ZERO_FLAG){
	//		m_movingDuration=BEVEL_VECTOR *1000;
	//	}else{
	//		m_movingDuration=0;
	//	}
	//}
	

}

/**
 * directionX -1,0,1
 */
void GridMoveComponent::calcSpeedVector(float directionX,float directionY)
{
	int i=floor(directionX+FLOAT_ZERO_FLAG);
	int j=floor(directionY+FLOAT_ZERO_FLAG);

	if(i==0||j==0){
		//m_speedX,m_speedY其中一个为0或都为0
		m_speedX=i*m_speed*AXIS_VECTOR;
		m_speedY=j*m_speed*AXIS_VECTOR;
	}else{
		//m_speedX,m_speedY都不为0，为speed的sqrt(2)/2
		//speed的大小不变，分量的是变化的。由于是45度地图，所以只有一种变化sqrt(2)/2
		m_speedX=i*m_speed*BEVEL_VECTOR_HALF;
		m_speedY=j*m_speed*BEVEL_VECTOR_HALF;
	}
}

/**
 * 移动动画步骤
 * 现在直接使用地图坐标
 * 以后优化使用view视图的坐标，减少坐标转换
 */
void GridMoveComponent::updateDirection( float delta)
{
	WorldEntity* owner=(WorldEntity*)m_owner;
	float mx=owner->getX(),my=owner->getY();

	m_movingDeltaTime+=delta;
	if(m_movingDeltaTime<m_movingDuration){
		mx+=delta*m_speedX;
		my+=delta*m_speedY;
	}else{
		//一次移动完成
		mx=m_to.x;
		my=m_to.y;
		if (m_moveState==MoveContinue) {

		}else{
			m_moveState=MoveWillStop;
			stopMove();
		}
		
	}
	owner->setCoordinate(mx,my);
    
}

/**
 * 按指定路径移动
 */
void GridMoveComponent::moveWithPaths(CCArray* paths)
{
	moveWithPaths(paths ,0);
}

void GridMoveComponent::moveWithPaths(CCArray* paths,int fromIndex)
{
	m_update=schedule_selector(GridMoveComponent::updatePath);

	if (m_moveState==MoveStart) {
		m_iFromIndex=fromIndex;
		continueMoveWithPaths(paths);
	}else if(m_moveState==MoveStop){
		m_iFromIndex=fromIndex;
		this->setCurrentPaths(paths);
		preparePath();
		if (beforeMovePath()) {
			startMove();
		}
	}
}
/**
 * 继续指定路径移动
 */
void GridMoveComponent::continueMoveWithPaths(CCArray* paths)
{
	this->setNextPaths(paths);	
	m_moveState=MoveContinue;
}

/**
 * 路径移动之前进行检查
 */
bool GridMoveComponent::beforeMovePath()
{
	if(beforeMove()){
		calcDirection();
		return true;
	}
	return false;
}

void GridMoveComponent::restartMove()
{
	m_moveState=MoveStart;
	preparePath();
	beforeMovePath();
}

/**
 * 准备移动路径
 */
void  GridMoveComponent::preparePath()
{
	m_iPathIndex=m_pCurrentPaths->count()-2-m_iFromIndex;
	if (m_iPathIndex<0) {
		CCAssert(m_iPathIndex<0,"paths length less 2");
	}
	
	m_to=*(CCPoint*)m_pCurrentPaths->objectAtIndex(m_iPathIndex);

}

/**
 * 计算方向
 * 主要用于按路径移动时
 */
void GridMoveComponent::calcDirection()
{
	GameEntity* owner=(GameEntity*)m_owner;
	CCPoint pos=owner->getPosition();
	m_directionX=m_to.x>pos.x?1:m_to.x<pos.y?-1:0;
	m_directionY=m_to.y>pos.y?1:m_to.y<pos.y?-1:0;
}



/**
 * 移动动画步骤
 * 通过路径移动的动画步骤
 */
void GridMoveComponent::updatePath(float delta)
{
    GameEntity* owner=(GameEntity*)m_owner;
    
    CCPoint pos=owner->getPosition();
	//根据速度计算移动距离
    float s=delta*10;
	pos.x+=s*m_speedX;
	pos.y+=s*m_speedY;
    
//    CCLOG("x:%f,y:%f",pos.x,pos.y);
	//判断是否结束	
	if (m_hasEndPosition && (m_directionFlagX * pos.x>m_directionFlagX*m_to.x  || fabs(pos.x-m_to.x)<0.00001) &&  (m_directionFlagY*pos.y> m_directionFlagY* m_to.y|| fabs(pos.y-m_to.y)<0.00001)) {
		pos.x=m_to.x;
		pos.y=m_to.y;

		if (m_moveState==MoveContinue) {
			if (m_pNextPaths!=NULL) {
				m_moveState=MoveStart;
				this->setCurrentPaths(m_pNextPaths);
				preparePath();
				beforeMovePath();
			}
		}else if (--m_iPathIndex>=0 && m_moveState==MoveStart) {
			//进行下一个格子
			m_to=*(CCPoint*)m_pCurrentPaths->objectAtIndex(m_iPathIndex);
			beforeMovePath();
		}else {
			//stop move
			this->setCurrentPaths(NULL);
			m_moveState=MoveWillStop;//标记将要结束
			stopMove();
		}
	}
	owner->setPosition(pos);
}



///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(float) dirX dirY:(float)dirY
//{
//	m_lastDirection=m_direction;
//	
//	m_direction.x=dirX;
//	m_direction.y=dirY;
//	
//	m_to.x=m_owner.mx+dirX;
//	m_to.y=m_owner.my+dirY;
//}
//
///**
// * 设置方向
// * 用于按方向移动
// */
//void setDirection:(CGPoint) dir
//{
//	m_lastDirection=m_direction;
//	
//	m_direction=dir;
//	
//	m_to.x=m_owner.mx+dir.x;
//	m_to.y=m_owner.my+dir.y;
//}
//
//void clearMapData
//{
//	MapData *mapData=[MapData sharedMapData];
//	int x,y;
//	if (m_moveState!=MoveStop) {
//		x=(int)m_to.x;
//		y=(int)m_to.y;
//	}else {
//		x=(int)mx;
//		y=(int)my;
//	}
//	
//	for ( int i=0; i<l_; i++) {
//		for (int j=0; j<b_; j++) {
//			[mapData removeMapInfoWithX:x+j y:y+i entity:self];
//		}
//	}
//}
/**
 * 方向改变
 * 人物在移动时要面向不同的方向
 */
void GridMoveComponent::updateMoveAnimation()
{
	//+0.5四舍五入
	int i=floor(m_directionX+0.5)+1;
	int j=floor(m_directionY+0.5)+1;
	int index=directionMapping[i][j];
	CCLOG("index:%d,%d,%d,%f,%f",index,i,j,m_directionX,m_directionY);
	if (index>-1) {
		CCDictionary* data=new CCDictionary();
		data->setObject(CCString::create("move"), "name");
		data->setObject(CCInteger::create(index), "direction");
    
		CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_owner,data);
	}
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void GridMoveComponent::doMoveStart()
{
    //todo parse direction
    updateMoveAnimation();
   
}

/**
 * 移动结束
 * 由移动状态转向空闲状态
 */
void GridMoveComponent::doMoveStop()
{
	CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_owner,data);

}
//处理碰撞,由子类实现。
//TODO:触发事件。由事件接收者执行处理逻辑，比如重新寻路。、
void GridMoveComponent::doHit(CCPoint location)
{
	
}

float GridMoveComponent::getSpeed()
{
    return m_speed;
}

void GridMoveComponent::setSpeed(float speed)
{
    m_speed=speed;
}

void GridMoveComponent::setDirection(float directionX,float directionY)
{
	m_directionX=directionX;
	m_directionY=directionY;

}

void GridMoveComponent::setDirection(CCPoint direction)
{
	m_directionX=direction.x;
	m_directionY=direction.y;
}

CCPoint GridMoveComponent::getDirection()
{
    return ccp(m_directionX,m_directionY);
}

void GridMoveComponent::setDirectionX(float directionX)
{
    m_directionX = directionX;
}

float GridMoveComponent::getDirectionX()
{
    return m_directionX;
}

void GridMoveComponent::setDirectionY(float directionY)
{
    m_directionY = directionY;
}

float GridMoveComponent::getDirectionY()
{
    return m_directionY;
}

void GridMoveComponent::setNextDirection(float directionX,float directionY)
{
	m_nextDirectionX=directionX;
	m_nextDirectionY=directionY;
}
CCPoint GridMoveComponent::getNextDirection()
{
	return ccp(m_nextDirectionX,m_nextDirectionY);
}

void GridMoveComponent::setNextDirectionX(int nextDirectionX)
{
    m_nextDirectionX = nextDirectionX;
}

int GridMoveComponent::getNextDirectionX()
{
    return m_nextDirectionX;
}

void GridMoveComponent::setNextDirectionY(float nextDirectionY)
{
    m_nextDirectionY = nextDirectionY;
}

float GridMoveComponent::getNextDirectionY()
{
    return m_nextDirectionY;
}

CCPoint GridMoveComponent::getTo()
{
    return m_to;
}

void GridMoveComponent::setTo(CCPoint to)
{
    m_to=to;
}

void GridMoveComponent::setCurrentPaths(CCArray* pCurrentPaths)
{
    CC_SAFE_RETAIN(pCurrentPaths);
    CC_SAFE_RELEASE(m_pCurrentPaths);
    m_pCurrentPaths = pCurrentPaths;
}

CCArray* GridMoveComponent::getCurrentPaths()
{
    return m_pCurrentPaths;
}

void GridMoveComponent::setNextPaths(CCArray* pNextPaths)
{
    CC_SAFE_RETAIN(pNextPaths);
    CC_SAFE_RELEASE(m_pNextPaths);
    m_pNextPaths = pNextPaths;
}

CCArray* GridMoveComponent::getNextPaths()
{
    return m_pNextPaths;
}



NS_YH_END
