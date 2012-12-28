#ifndef SCENES_GAME_SCENE_H_
#define SCENES_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "GameWorld.h"

USING_NS_CC;

NS_YH_BEGIN

class GameScene : CCLayer {
public:
    
    GameScene();
    ~GameScene();

    virtual bool init();

    static CCScene* scene();

    CCPoint locationFromTouch(CCTouch* touch);

    CREATE_FUNC(GameScene);

    void setGameWorld(GameWorld* pGameWorld);
    GameWorld* getGameWorld();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); 
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 

private:
    GameWorld* m_pGameWorld;
};

NS_YH_END

#endif //SCENES_GAME_SCENE_H_