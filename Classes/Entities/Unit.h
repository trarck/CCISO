#ifndef ENTITIES_UNIT_H_
#define ENTITIES_UNIT_H_

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "WorldEntity.h"

USING_NS_CC;

NS_YH_BEGIN


class Unit : public WorldEntity {
    //等级
    CC_PROPERTY(float, m_level, Level)
    //生命值
    CC_PROPERTY(float, m_health,Health)
    
    CC_PROPERTY(float, m_maxHealth,MaxHealth)
    //魔法值
    CC_PROPERTY(float, m_mana,Mana)
    CC_PROPERTY(float, m_maxMana,MaxMana)
    //防御值 可以再分为物防和法防
	CC_PROPERTY(float, m_defence,Defence)
	CC_PROPERTY(float, m_magicDefence,MagicDefence)
//    //护甲
//    CC_PROPERTY(float, m_armor,armor)
    //其它属性
    //力量
    CC_PROPERTY(float, m_strengh,Strengh)
    //敏捷
    CC_PROPERTY(float, m_dexterity,Dexterity)
    //智力
    CC_PROPERTY(float, m_intelligence,Intelligence)

    
public:
    
    Unit();
    ~Unit();
    
//    virtual bool init();
    
    
   

protected:
    //等级
//	int m_level;
//    //生命值
//    float m_health;
//    float m_maxHealth;
//    //魔法值
//    float m_mana;
//    float m_maxMana;
//    //防御值 可以再分为物防和法防
//	float m_defence;
//	float m_magicDefence;
//    //    //护甲
//    //    float armor;
//    //其它属性
//    //力量
//    float m_strengh;
//    //敏捷
//    float m_dexterity;
//    //智力
//    float m_intelligence;

};

NS_YH_END


#endif //ENTITIES_UNIT_H_