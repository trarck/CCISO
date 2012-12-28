#ifndef SCENES_GAME_OVER_SCENE_H_
#define SCENES_GAME_OVER_SCENE_H_


#include "cocos2d.h"
#include "GameConfig.h"


USING_NS_CC;

NS_YH_BEGIN

class GameOverScene : public CCLayer {
public:
    virtual bool init();
    static CCScene* scene();
    
	void menuStartCallback(CCObject* pSender);
    void menuQuitCallback(CCObject* pSender);

    CREATE_FUNC(GameOverScene);
};

NS_YH_END

#endif //SCENES_GAME_OVER_SCENE_H_
