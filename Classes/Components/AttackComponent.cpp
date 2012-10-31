#include "AttackComponent.h"
#include "CCMessageManager.h"
#include "GameMessages.h"

USING_NS_CC;

NS_YH_BEGIN

AttackComponent::AttackComponent()
:m_target(NULL)
{
    CCLOG("AttackComponent create");
    m_name="AttackComponent";
}

AttackComponent::~AttackComponent()
{
    CCLOG("AttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool AttackComponent::init()
{
    CCLOG("AttackComponent init");
    return true;
}

void AttackComponent::handleMessage(CCMessage *message)
{
    CCLOG("AttackComponent::handleMessage");
    CCLOG("get message %d",message->getType());

    Unit* target;
	switch(message->getType()){
		
		case ATTACK:
            target=(Unit*)message->getData();
            if(target){
                setTarget(target);
            }
			attack();
			break;
		case DIE:
            didTargetDie();
			break;
        case SET_ATTACK_TARGET:
            setTarget((Unit*)message->getData());
            break;

	}
}

bool AttackComponent::registerMessages()
{
    CCLOG("AttackComponent::registerMessages");
    
    CCMessageManager::defaultManager()->registerReceiver(m_owner, message_selector(AttackComponent::handleMessage), SET_ATTACK_TARGET, NULL,this);
    
    CCMessageManager::defaultManager()->registerReceiver(m_owner, message_selector(AttackComponent::handleMessage), ATTACK, NULL,this);
    
    return true;
}

void AttackComponent::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}



void AttackComponent::attack()
{
    if(m_target){
        CCLOG("AttackComponent::startAttack");
        int targetHp=m_target->getHealth();
        CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
        m_target->setHealth(targetHp-1);
    }else {
        CCLOG("AttackComponent::startAttack no target");
    }
}



void AttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

void AttackComponent::didTargetDie()
{
    CCLOG("target is die");
    
    //remove message
    CCMessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(AttackComponent::handleMessage));
    CC_SAFE_RELEASE(m_target);
    m_target=NULL;
}

Unit* AttackComponent::getTarget()
{
    return m_target;
}

void AttackComponent::setTarget(Unit* target)
{
    if(target!=m_target){
        CCMessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(AttackComponent::handleMessage));
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target=target;

        CCMessageManager::defaultManager()->registerReceiver(this, message_selector(AttackComponent::handleMessage), DIE, m_target);
    }
}

NS_YH_END

