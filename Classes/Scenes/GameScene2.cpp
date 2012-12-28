#include "cocos2d.h"
#include "GameScene.h"
//#include "GameWorld.h"

//+(CGPoint) locationFromTouch:(UITouch *) touch
//{
//	CGPoint touchLocation=[touch locationInView:[touch view]];
//	return [[CCDirector sharedDirector] convertToGL:touchLocation];
//}

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene* layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init
{
    if(!CCLayer::init()){
        return false;
    }

				
    self.gameWorld=[GameWorld sharedGameWorld];
    [self addChild:gameWorld_];
    gameWorld_.mapId=1;
    [gameWorld_ release];

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
