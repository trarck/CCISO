//
//  GameMessage.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#ifndef GAME_MESSAGES_H_
#define GAME_MESSAGES_H_

#include "CCMessage.h"

enum GameMessage
{
    ALL=0,
    ANIMATION,
    CHANGE_ANIMATION,
    //attack
    ATTACK,
    SET_ATTACK_TARGET,
    AUTO_ATTACK,
    DIE,
    //move
    MOVE_TO,
    MOVE_DIRECTION,
    MOVE_DIRECTION_TO,
    MOVE_DIRECTION_STOP,
	MOVE_PATH
};



#endif //GAME_MESSAGES_H_
