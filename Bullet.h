/*
 * Bullet.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#ifndef BULLET_H_
#define BULLET_H_
#include "Common.h"
#include "Entity.h"
#include <cmath>

class Bullet: public Entity
{
public:
	Bullet();
	virtual ~Bullet();

	void  update();

};
#endif /* BULLET_H_ */
