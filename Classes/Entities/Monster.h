#ifndef ENTITIES_MONSTER_H_
#define ENTITIES_MONSTER_H_

#include "cocos2d.h"
#include "GameEntity.h"

USING_NS_CC;

NS_YH_BEGIN

class Monster : public GameEntity {
public:
    Monster();
    ~Monster();
    
    virtual void setupComponents();

};

NS_YH_END

#endif //ENTITIES_MONSTER_H_
