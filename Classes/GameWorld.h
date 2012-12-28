#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameConfig.h"

#ifndef CCISO_GAMEWORLD_H_
#define CCISO_GAMEWORLD_H_

USING_NS_CC;

NS_YH_BEGIN

class GameWorld: public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);
};
NS_YH_END
#endif // CCISO_GAMEWORLD_H_
