#ifndef CCISO_GAMECAMERA_H_
#define CCISO_GAMECAMERA_H_

#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;

NS_YH_BEGIN

class GameWorld;

class GameCamera: public CCObject
{
public:
	GameCamera();
	~GameCamera();
    bool init();  
	
    //CREATE_FUNC(GameCamera);

	void move(float deltaX,float deltaY);
    void moveTo(float x,float y);

	void moveOpposite(float deltaX,float deltaY);

    CCPoint getLocationInWorld(const CCPoint& position);

    virtual void setGameWorld(GameWorld* const pGameWorld);
    virtual GameWorld* getGameWorld();
    virtual void setSmoothMove(bool bSmoothMove);
    virtual bool isSmoothMove();

protected:
	GameWorld* m_pGameWorld;
    bool m_bSmoothMove;

    float m_fPositionX;
    float m_fPositionY;
    CCPoint m_tWorldPosition;
};

NS_YH_END

#endif // CCISO_GAMECAMERA_H_
