//
//  GamveStartScene.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-14.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "GameStartScene.h"
#include "GameScene.h"

USING_NS_CC;

NS_YH_BEGIN


CCScene* GameStartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameStartScene* gameStartScene = GameStartScene::node();

    // add layer as a child to scene
    scene->addChild(gameStartScene);

    // return the scene
    return scene;
}

bool init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemFont->setFontName("Marker Felt");
    CCMenuItemFont->setFontSize(30);
    
    CCMenuItem* start=CCMenuItemFont::itemFromString("start game",this 
                                            menu_selector(GameStartScene::startGame));
    CCMenuItem* quit=CCMenuItemFont::itemFromString("quit game" ,this
                                           menu_selector(GameStartScene::quitGame));
    
    CCMenu* menu=CCMenu::create(start,quit,NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
	return true;
}

void GameStartScene::startGame(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void GameStartScene::quitGame(CCObject* sender)
{
	CCLOG("quit game");
     this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
