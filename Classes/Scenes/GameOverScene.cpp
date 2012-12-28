//
//  GameOver.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-14.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "GameOverScene.h"
#include "GameScene.h"

NS_YH_BEGIN
CCScene* GameOverScene::scene()
{
     // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOverScene* gameOverScene = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(gameOverScene);
    // return the scene
    return scene;
}

bool GameOverScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(30);
    
    CCMenuItem* pStart=CCMenuItemFont::create("start game",this,menu_selector(GameOverScene::menuStartCallback));
    CCMenuItem* pQuit=CCMenuItemFont::create("quit game",this,menu_selector(GameOverScene::menuQuitCallback));
    
    CCMenu* pMenu=CCMenu::create(pStart,pQuit,NULL);
    pMenu->alignItemsVertically();
    this->addChild(pMenu);

	return true;
}

void GameOverScene::menuStartCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}

void GameOverScene::menuQuitCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
NS_YH_END
