#include "GameWorld.h"
#include "GameMessages.h"
#include "CCMessageManager.h"
#include "ISOCoordinateLayer.h"
#include "GameCamera.h"

USING_NS_CC;

NS_YH_BEGIN

GameCamera::GameCamera()
:m_fPositionX(0)
,m_fPositionY(0)
,m_pWorldPosition(NULL)
,m_pGameWorld(NULL)
{
    
}

GameCamera::~GameCamera()
{
    CC_SAFE_RELEASE(m_pWorldPosition);
}

bool GameCamera::init()
{
    m_pWorldPosition=new CCPoint(0,0);
	return true;
}

void  GameCamera::move(float deltaX,float deltaY)
{
    m_pWorldPosition->x-=deltaX;
    m_pWorldPosition->y-=deltaY;

    m_pGameWorld->setPosition(*m_pWorldPosition);
}

void  GameCamera::moveTo(float x,float y)
{
    m_pWorldPosition->x=-x;
    m_pWorldPosition->y=-y;

    m_pGameWorld->setPosition(*m_pWorldPosition);
}

void  GameCamera::moveOpposite(float deltaX,float deltaY)
{
    m_pWorldPosition->x+=deltaX;
    m_pWorldPosition->y+=deltaY;

    m_pGameWorld->setPosition(ccp(m_pWorldPosition->x,m_pWorldPosition->y));
}

CCPoint  GameCamera::getLocationInWorld(const CCPoint& position)
{
    return ccp(position.x-m_pWorldPosition->x,position.y-m_pWorldPosition->y);
}

void GameCamera::setGameWorld(GameWorld* const pGameWorld)
{
    m_pGameWorld = pGameWorld;
}

GameWorld* GameCamera::getGameWorld()
{
    return m_pGameWorld;
}

void GameCamera::setSmoothMove(bool bSmoothMove)
{
    m_bSmoothMove = bSmoothMove;
}

bool GameCamera::isSmoothMove()
{
    return m_bSmoothMove;
}
NS_YH_END