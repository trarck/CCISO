//
//  GamveStartScene.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-14.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#import "GameStartScene.h"
#import	"GameScene.h"

@implementation GameStartScene

+(id) scene
{
	CCScene *scene=[CCScene node];
	GameStartScene *gameStartScene=[GameStartScene node];
	[scene addChild:gameStartScene];
	return scene;
}

-(id) init
{
	if((self=[super init])){
		[CCMenuItemFont setFontName:@"Marker Felt"];
		[CCMenuItemFont setFontSize:30];
		
		CCMenuItem *start=[CCMenuItemFont itemFromString:@"start game" 
												  target:self 
												selector:@selector(startGame:)];
		CCMenuItem *quit=[CCMenuItemFont itemFromString:@"quit game" 
												 target:self
											   selector:@selector(quitGame:)];
		
		CCMenu *menu=[CCMenu menuWithItems:start,quit,nil];
		[menu alignItemsVertically];
		[self addChild:menu];
	}
	return self;
}

-(void) startGame:(id) sender
{
	[[CCDirector sharedDirector] replaceScene:[GameScene scene]];
}

-(void) quitGame:(id) sender
{
	NSLog(@"quit game");
}
@end
