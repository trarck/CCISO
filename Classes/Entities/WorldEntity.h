#ifndef ENTITIES_WORLD_ENTITY_H_
#define ENTITIES_WORLD_ENTITY_H_

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "GameTypes.h"
#include "GameMacros.h"
#include "GameEntity.h"

USING_NS_CC;

NS_YH_BEGIN


class WorldEntity : public GameEntity {
public:
    
    WorldEntity();
    ~WorldEntity();
    
    virtual bool init();
    virtual bool init(int entityId,int l,int b,int h,bool barrier);
    virtual bool init(CCDictionary* data);
    
    
    
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
    
    inline Vector3F getCoordinate()
    {
        Vector3F coordinate={m_x,m_y,m_z};
        return coordinate;
    };
    
    inline void setCoordinate(Vector3F coordinate)
    {
        m_x=coordinate.x;
        m_y=coordinate.y;
        m_z=coordinate.z;
    }
    
    
    inline void setX(float x){
        m_x=x;
    };
    
    inline float getX(){
        return m_x;
    };
    
    inline void setY(float y){
        m_y=y;
    };
    
    inline float getY(){
        return m_y;
    };
    
    inline void setZ(float z){
        m_z=z;
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
    
    CCObject* m_gameWorld;
    
    bool m_barrier;
    
};

NS_YH_END


#endif //ENTITIES_WORLD_ENTITY_H_