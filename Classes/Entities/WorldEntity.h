#ifndef ENTITIES_WORLD_ENTITY_H_
#define ENTITIES_WORLD_ENTITY_H_

#include "cocos2d.h"
#include "GameConfig.h"
#include "CCMessageHandler.h"
#include "GameEntity.h"


USING_NS_CC;

NS_YH_BEGIN


class WorldEntity : public GameEntity {
public:
    
    WorldEntity();
    ~WorldEntity();
    
    virtual bool init();
	virtual bool init(int entityId);
    virtual bool init(int entityId,int l,int b,int h,bool barrier);
//    virtual bool initWithData(CCDictionary* data);
    
    //virtual void visit(void);
    
    //get set
    
    //size
    inline void setL(int l){
        m_l=l;
    };
    
    inline int getL(){
        return m_l;
    };
    
    inline void setB(int b){
        m_b=b;
    };
    
    inline int getB(){
        return m_b;
    };
    
    inline void setH(int h){
        m_h=h;
    };
    
    inline int getH(){
        return m_h;
    };

    //coordinate

	inline void setCoordinateAndTranslate(Vector3F coordinate)
    {
        m_x=coordinate.x;
        m_y=coordinate.y;
        m_z=coordinate.z;
		this->setPosition(isoGameToView3F(m_x,m_y,m_z));
    }

	inline void setCoordinateAndTranslate(float x,float y,float z){
		m_x=x;
        m_y=y;
        m_z=z;
		this->setPosition(isoGameToView3F(m_x,m_y,m_z));
	}
    
	inline void setCoordinateAndTranslate(CCPoint coordinate)
    {
        m_x=coordinate.x;
        m_y=coordinate.y;
        m_z=0;
		this->setPosition(isoGameToView2F(m_x,m_y));
    }
	inline void setCoordinateAndTranslate(float x,float y)
    {
        m_x=x;
        m_y=y;
        m_z=0;
		this->setPosition(isoGameToView2F(x,y));
    }
    
    inline Vector3F getCoordinate3F()
    {
		Vector3F coordinate={ m_x, m_y, m_z };
        return coordinate;
    };
    
    inline void setCoordinate(Vector3F coordinate)
    {
        m_x=coordinate.x;
        m_y=coordinate.y;
        m_z=coordinate.z;
		m_bCoordinate_dirty=true;
    }

	inline void setCoordinate(float x,float y,float z){
		m_x=x;
        m_y=y;
        m_z=z;
		m_bCoordinate_dirty=true;
	}


	inline CCPoint getCoordinate()
    {
        return ccp(m_x,m_y);
    };
    
	inline void setCoordinate(CCPoint coordinate)
    {
        m_x=coordinate.x;
        m_y=coordinate.y;
        m_z=0;
		m_bCoordinate_dirty=true;
    }
	inline void setCoordinate(float x,float y)
    {
        m_x=x;
        m_y=y;
        m_z=0;
		m_bCoordinate_dirty=true;
    }
    
    
    inline void setX(float x){
        m_x=x;
		m_bCoordinate_dirty=true;
    };
    
    inline float getX(){
        return m_x;
    };
    
    inline void setY(float y){
        m_y=y;
		m_bCoordinate_dirty=true;
    };
    
    inline float getY(){
        return m_y;
    };
    
    inline void setZ(float z){
        m_z=z;
		m_bCoordinate_dirty=true;
    };
    
    inline float getZ(){
        return m_z;
    };
    
    
    inline void setGameWorld(CCObject* gameWorld){
        m_gameWorld=gameWorld;
    };
    
    inline CCObject* getGameWorld(){
        return m_gameWorld;
    };
    
    inline void setBarrier(bool barrier){
        m_barrier=barrier;
    };
    
    inline bool isBarrier(){
        return m_barrier;
    };
    
	void setMoving(bool bMoving){
		m_bMoving=bMoving;
	};
	bool isMoving(){
		return m_bMoving;
	};
	void setMovend(float x,float y)
	{
		m_MovendX=x;
		m_MovendY=y;
	};
	CCPoint getMovingCoorinate()
	{
		return ccp(m_MovendX,m_MovendY);
	};
    
protected:
    //斜45中的三维大小
    //m_gameSize;
    int m_l;
    int m_b;
    int m_h;
    float m_x;
    float m_y;
    float m_z;
    
    Vector3F m_coordinate;
	bool m_bCoordinate_dirty;
    
    CCObject* m_gameWorld;
    
    bool m_barrier;
    
	//正在移动的作坐
	bool m_bMoving;
	//如果移动完成时候的坐标。
	float m_MovendX;
	float m_MovendY;
};

NS_YH_END


#endif //ENTITIES_WORLD_ENTITY_H_