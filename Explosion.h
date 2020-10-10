/*
 * Explosion.h
 *
 *  Created on: Oct 8, 2020
 *      Author: dean
 */

#ifndef EXPLOSION_H_
#define EXPLOSION_H_
#include "Entity.h"

class Explosion: public Entity {
public:
	Explosion();
	virtual ~Explosion();
	void update();
};

#endif /* EXPLOSION_H_ */
