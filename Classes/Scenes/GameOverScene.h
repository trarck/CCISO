#ifndef SCENES_GAMEOVERSCENE_H_
#define SCENES_GAMEOVERSCENE_H_

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

#endif //SCENES_GAMEOVERSCENE_H_
