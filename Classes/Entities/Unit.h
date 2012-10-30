#ifndef ENTITIES_UNIT_H_
#define ENTITIES_UNIT_H_

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "WorldEntity.h"

USING_NS_CC;

NS_YH_BEGIN


class Unit : public WorldEntity {
public:
    
    Unit();
    ~Unit();
    
    virtual bool init();
    
    
    
protected:
    //等级
	int m_level;
    //生命值
    float m_health;
    float m_maxHealth;
    //魔法值
    float m_mana;
    float m_maxMana;
    //防御值 可以再分为物防和法防
	float m_defence;
	float m_magicDefence;
    //其它属性
    //力量
    float strengh;
    //敏捷
    float dexterity;
    //智力
    float intelligence;
//    //护甲
//    float armor;
};

NS_YH_END


#endif //ENTITIES_UNIT_H_