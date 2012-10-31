#ifndef __Manual_Attack_Component_H__
#define __Manual_Attack_Component_H__

#include "cocos2d.h"
#include "AttackComponent.h"
#include "GameEntity.h"

USING_NS_CC;

NS_YH_BEGIN


class ManualAttackComponent : public AttackComponent 
{
public:
    ManualAttackComponent();
    ~ManualAttackComponent();
    virtual bool init();
    
    
    //property
};

NS_YH_END

#endif //__Manual_Attack_Component_H__
