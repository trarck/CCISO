#include "CCMessageManager.h"
#include "GameMessages.h"
#include "WorldEntity.h"

USING_NS_CC;

NS_YH_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

WorldEntity::WorldEntity()
:m_l(0)
,m_b(0)
,m_h(0)
,m_x(0.0f)
,m_y(0.0f)
,m_z(0.0f)
,m_barrier(true)
,m_gameWorld(NULL)
,m_bCoordinate_dirty(false)
//,m_view(NULL)
{
    CCLOG("WorldEntity create");
    m_components=new CCDictionary();
}

WorldEntity::~WorldEntity()
{
    CCLOG("WorldEntity destroy");  
}

bool WorldEntity::init()
{
    if(!GameEntity::init()){
		return false;
	}
    
    return true;
}

bool WorldEntity::init(int entityId)
{
    if(!GameEntity::init(entityId)){
		return false;
	}
    
    return true;
}

bool WorldEntity::init(int entityId, int l, int b, int h, bool barrier)
{
    GameEntity::init();
    
    return true;
}

//void WorldEntity::visit(void)
//{
//	if(m_bCoordinate_dirty)
//		this->setPosition(isoGameToView3F(m_x,m_y,m_z));
//
//	CCNode::visit();
//}

NS_YH_END
