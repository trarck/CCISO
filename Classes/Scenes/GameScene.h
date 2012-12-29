#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "cocos2d.h"
#include "Player.h"
#include "GameWorld.h"

USING_NS_CC;

NS_YH_BEGIN

class GameScene : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    
    CREATE_FUNC(GameScene);

	GameWorld* getGameWorld();
private:
    GameWorld* m_pGameWorld;
};

NS_YH_END

#endif // SCENES_GAMESCENE_H_
