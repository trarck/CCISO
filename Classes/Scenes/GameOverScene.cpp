//
//  GameOver.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-14.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#import "GameOverScene.h"
#import "GameScene.h"

@implementation GameOverScene

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	GameOverScene *layer = [GameOverScene node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(id) init
{
	if((self=[super init])){
		CCLabelTTF *gameOverlabel=[CCLabelTTF labelWithString:@"Game Over!" fontName:@"Marker Felt" fontSize:64]; 
		CGSize screenSize=[[CCDirector sharedDirector] winSize];
		gameOverlabel.position=ccp(screenSize.width/2,screenSize.height/2);
		[self addChild:gameOverlabel];
		
		//menu
		[CCMenuItemFont setFontName:@"Marker Felt"];
		[CCMenuItemFont setFontSize:30];
		
		CCMenuItem *restart=[CCMenuItemFont itemFromString:@"restart game" target:self selector:@selector(restart:)];
		
		CCMenu *menu=[CCMenu menuWithItems:restart,nil];
		[menu alignItemsHorizontally];
		menu.position=ccp(screenSize.width/2,30);
		[self addChild:menu];
		
	}
	return self;
}

-(void) restart:(id) sender
{
	[[CCDirector sharedDirector] replaceScene:[GameScene scene]];
}

@end
