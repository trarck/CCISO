#ifndef ENTITIES_GAME_ENTITY_H_
#define ENTITIES_GAME_ENTITY_H_

#include "cocos2d.h"
#include "GameMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "Component.h"

USING_NS_CC;


NS_YH_BEGIN

class GameEntity : public CCSprite {
public:
    
    GameEntity();
    ~GameEntity();
    
    virtual bool init();
    virtual bool init(int entityId);
    virtual bool init(CCDictionary* data);
    
    //get set
    int getEntityId();
    void setEntityId(int entityId);
    
    virtual CCSprite* view();
    virtual void view(CCSprite* view);
    
    //message operate
    virtual void registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender);
    virtual void unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender);
    virtual void sendMessage(MessageType type ,CCObject* receiver ,CCObject* data);
    virtual void sendMessage(MessageType type ,CCObject* receiver);
	virtual void cleanupMessages();
    
 
    //components
    virtual void setupComponents();
    
    void addComponent(Component* component){
        CCLOG("addComponent component named %s",component->getName());
        m_components->setObject(component, component->getName());
    };
    void addComponent(Component* component,const char *name){
        CCLOG("addComponent component named %s",name);
        m_components->setObject(component, name);
    };
    Component* getComponent(const char *name){
        return (Component*) m_components->objectForKey(name);
    };
    
    virtual void cleanup();
   
    
    
protected:
	int m_entityId;//game object id
    CCDictionary* m_components;
    
   
//    CCSprite* m_view;
};

NS_YH_END


#endif //ENTITIES_GAME_ENTITY_H_
