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
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameStartScene* layer = GameStartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameStartScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    

    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(30);
    
    CCMenuItem* pStart=CCMenuItemFont::create("start game",this,menu_selector(GameStartScene::menuStartCallback));
    CCMenuItem* pQuit=CCMenuItemFont::create("quit game",this,menu_selector(GameStartScene::menuQuitCallback));
    
    CCMenu* pMenu=CCMenu::create(pStart,pQuit,NULL);
    pMenu->alignItemsVertically();
    this->addChild(pMenu);

	return true;
}

void GameStartScene:menuStartCallback(CCObject* pSender)
{
    CCDirecto::sharedDirector()->replaceScene(GameScene::scene);
}

void GameStartScene:menuStartCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

NS_YH_END