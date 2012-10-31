#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

NS_YH_BEGIN

class Player : public Unit {
public:
    Player();
    ~Player();
    
    virtual void setupComponents();

protected:

};

NS_YH_END

#endif //ENTITIES_PLAYER_H_
