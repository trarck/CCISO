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
,m_tWorldPosition(CCPointZero)
,m_pGameWorld(NULL)
{
    
}

GameCamera::~GameCamera()
{

}

bool GameCamera::init()
{
	return true;
}

void  GameCamera::move(float deltaX,float deltaY)
{
    m_tWorldPosition.x-=deltaX;
    m_tWorldPosition.y-=deltaY;

    m_pGameWorld->setPosition(m_tWorldPosition);
    m_pGameWorld->updateMapPosition(ccp(-m_tWorldPosition.x,-m_tWorldPosition.y));
}

void  GameCamera::moveTo(float x,float y)
{
    m_tWorldPosition.x=-x;
    m_tWorldPosition.y=-y;

    m_pGameWorld->setPosition(m_tWorldPosition);
    m_pGameWorld->updateMapPosition(ccp(-m_tWorldPosition.x,-m_tWorldPosition.y));

}

void  GameCamera::moveOpposite(float deltaX,float deltaY)
{
    m_tWorldPosition.x+=deltaX;
    m_tWorldPosition.y+=deltaY;

    m_pGameWorld->setPosition(m_tWorldPosition);
    m_pGameWorld->updateMapPosition(ccp(-m_tWorldPosition.x,-m_tWorldPosition.y));
}

CCPoint  GameCamera::getLocationInWorld(const CCPoint& position)
{
    return ccp(position.x-m_tWorldPosition.x,position.y-m_tWorldPosition.y);
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