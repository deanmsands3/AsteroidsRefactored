/*
 * Player.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "Entity.h"

class Player: public Entity {
public:
	bool thrust;
	Player();
	virtual ~Player();
	void update();
};

#endif /* PLAYER_H_ */
