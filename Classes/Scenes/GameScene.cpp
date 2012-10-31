//
//  GameScene.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "GameScene.h"
#import "GameWorld.h"

@implementation GameScene

@synthesize gameWorld=gameWorld_;

+(CGPoint) locationFromTouch:(UITouch *) touch
{
	CGPoint touchLocation=[touch locationInView:[touch view]];
	return [[CCDirector sharedDirector] convertToGL:touchLocation];
}

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	GameScene *layer = [GameScene node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
-(id) init
{
	// always call "super" init
	// Apple recommends to re-assign "self" with the "super" return value
	if( (self=[super init])) {
				
		self.gameWorld=[GameWorld sharedGameWorld];
		[self addChild:gameWorld_];
		gameWorld_.mapId=1;
		[gameWorld_ release];
	}
	return self;
}

-(void) registerWithTouchDispatcher
{
	[[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:0 swallowsTouches:YES];
	
}

-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
	return YES;
}
-(void) ccTouchEnded:(UITouch *)touch withEvent:(UIEvent *)event
{
	//CGPoint location=[self convertTouchToNodeSpace:touch];
		
}

// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
	
	// in case you have something to dealloc, do it in this method
	// in this particular example nothing needs to be released.
	// cocos2d will automatically release all the children (Label)
	
	// don't forget to call "super dealloc"
	
	self.gameWorld=nil;
	NSLog(@"game:before GameScene dealloc.");
	[super dealloc];
	NSLog(@"game:end GameScene dealloc.");
}

@end
