//
//  GameScene.h
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "GameWorld.h"

@interface GameScene : CCLayer {
	GameWorld *gameWorld_;
}
@property(nonatomic,retain) GameWorld *gameWorld;

+(CGPoint) locationFromTouch:(UITouch*) touch; 
+(id) scene;
@end
