#include "Player.h"
#include "AnimationComponent.h"

#include "AttackComponent.h"
#include "GameMessages.h"
#include "AutoAttackComponent.h"
//#include "SimpleMoveComponent.h"
#include "GridMoveComponent.h"

NS_YH_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

Player::Player()
{
    CCLOG("Player create");
}

Player::~Player()
{
    CCLOG("Player destroy");
}

void Player::setupComponents()
{
	CCLOG("Player::setupComponent");
    
    //animation
    
    AnimationComponent* animationComponent=new AnimationComponent();
    animationComponent->init();
    animationComponent->setOwner(this);
    
    
    //move animation
    animationComponent->addActionList(
                                      AnimationComponent::eightDirectionActionListWithDir("characters/2/0", 10, CCSizeMake(62, 91), 0.15f, "%s/%02d%03d.png"), 
                                      "idle");
    
    animationComponent->addActionList(
                            AnimationComponent::eightDirectionActionListWithDir("characters/2/1", 8, CCSizeMake(74, 93), 0.1f, "%s/%02d%03d.png"), 
                            "move");
    CCLOG("animationComponent1 count=%d",animationComponent->retainCount());
    animationComponent->registerMessages();
    CCLOG("animationComponent2 count=%d",animationComponent->retainCount());
    addComponent(animationComponent);
	CCLOG("animationComponent3 count=%d",animationComponent->retainCount());
    animationComponent->release();
    CCLOG("animationComponent4 count=%d",animationComponent->retainCount());
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    sendMessage(CHANGE_ANIMATION, this, data);
//    CCLOG("set begin action after");
    //attack
    
    AttackComponent* attackComponent=new AttackComponent();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    attackComponent->init();
    attackComponent->setOwner(this);
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    attackComponent->registerMessages();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    
    addComponent(attackComponent);
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    
   
    attackComponent->release();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    
    //auto attack
    AutoAttackComponent* autoAttackComponent=new AutoAttackComponent();
    autoAttackComponent->init();
    autoAttackComponent->setOwner(this);
    autoAttackComponent->registerMessages();
    addComponent(autoAttackComponent);
    autoAttackComponent->release();
    
    
    //SimpleMoveComponent* simpleMoveComponent=new SimpleMoveComponent();
    //simpleMoveComponent->initWithSpeed(2);
    //simpleMoveComponent->setOwner(this);
    //simpleMoveComponent->registerMessages();
    //addComponent(simpleMoveComponent);
    //simpleMoveComponent->release();

	GridMoveComponent* gridMoveComponent=new GridMoveComponent();
    gridMoveComponent->init(2);
    gridMoveComponent->setOwner(this);
    gridMoveComponent->registerMessages();
    addComponent(gridMoveComponent);
    gridMoveComponent->release();

}

NS_YH_END
