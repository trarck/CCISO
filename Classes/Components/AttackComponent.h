#ifndef __Attack_Component_H__
#define __Attack_Component_H__

#include "cocos2d.h"
#include "Component.h"
#include "Unit.h"

USING_NS_CC;

NS_YH_BEGIN


class AttackComponent : public Component 
{
public:
    AttackComponent();
    ~AttackComponent();
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    virtual void cleanupMessages();
    
    virtual void attack();
    virtual void attackWithSkillId(int skillId);
    
    virtual void didTargetDie();
    //property
    
    
    virtual void setTarget(Unit* target);
    Unit* getTarget();
    
protected:
    Unit* m_target;
};

NS_YH_END

#endif //__Attack_Component_H__
