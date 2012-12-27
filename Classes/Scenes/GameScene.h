#ifndef SCENES_GAME_SCENE_H_
#define SCENES_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameConfigs.h"
#include "GameWorld.h"

USING_NS_CC;

NS_YH_BEGIN

class GameScene : CCLayer {
public:
    virtual bool init();
   

    static CCScene* scene();

    CCPoint locationFromTouch(UITouch* touch);

    CREATE_FUNC(GameScene);

    void setGameWorld(GameWorld* pGameWorld);
    GameWorld* getGameWorld();

private:
    GameWorld* m_pGameWorld;
};

NS_YH_END

#endif //SCENES_GAME_SCENE_H_


