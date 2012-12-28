#ifndef SCENES_GAME_OVER_SCENE_H_
#define SCENES_GAME_OVER_SCENE_H_


#include "cocos2d.h"
#include "GameConfigs.h"


USING_NS_CC;

NS_YH_BEGIN

class GameOverScene : CCLayer {
public:
    virtual bool init();
    static CCScene* scene();
    
    CREATE_FUNC(GameOverScene);
};

NS_YH_END

#endif //SCENES_GAME_OVER_SCENE_H_
