#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "cocos2d.h"
#include "GameConfigs.h"


USING_NS_CC;

NS_YH_BEGIN

class GameScene : CCLayer {
public:
    virtual bool init();
    
    
    static CCScene* scene();
    
    CREATE_FUNC(GameScene);
   
    
};

NS_YH_END

#endif //SCENES_GAMESCENE_H_