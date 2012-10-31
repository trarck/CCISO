#include "CCMessageManager.h"
#include "GameMessages.h"
#include "Unit.h"

NS_YH_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

Unit::Unit()
:m_level(0.0f)
,m_health(0.0f)
,m_maxHealth(0.0f)
,m_mana(0.0f)
,m_maxMana(0.0f)
,m_defence(0.0f)
,m_magicDefence(0.0f)
,m_strengh(0.0f)
,m_dexterity(0.0f)
,m_intelligence(0.0f)
{
    CCLOG("Unit create");
}

Unit::~Unit()
{
    CCLOG("Unit destroy");
}

void Unit::setLevel(float level)
{
    m_level = level;
}

float Unit::getLevel()
{
    return m_level;
}

void Unit::setHealth(float health)
{
    m_health = health;
}

float Unit::getHealth()
{
    return m_health;
}

void Unit::setMaxHealth(float maxHealth)
{
    m_maxHealth = maxHealth;
}

float Unit::getMaxHealth()
{
    return m_maxHealth;
}

void Unit::setMana(float mana)
{
    m_mana = mana;
}

float Unit::getMana()
{
    return m_mana;
}

void Unit::setMaxMana(float maxMana)
{
    m_maxMana = maxMana;
}

float Unit::getMaxMana()
{
    return m_maxMana;
}

void Unit::setDefence(float defence)
{
    m_defence = defence;
}

float Unit::getDefence()
{
    return m_defence;
}

void Unit::setMagicDefence(float magicDefence)
{
    m_magicDefence = magicDefence;
}

float Unit::getMagicDefence()
{
    return m_magicDefence;
}

void Unit::setStrengh(float strengh)
{
    m_strengh = strengh;
}

float Unit::getStrengh()
{
    return m_strengh;
}

void Unit::setDexterity(float dexterity)
{
    m_dexterity = dexterity;
}

float Unit::getDexterity()
{
    return m_dexterity;
}

void Unit::setIntelligence(float intelligence)
{
    m_intelligence = intelligence;
}

float Unit::getIntelligence()
{
    return m_intelligence;
}

NS_YH_END
