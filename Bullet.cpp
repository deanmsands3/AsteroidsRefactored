/*
 * Bullet.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#include "Bullet.h"

Bullet::Bullet(){
	name="bullet";
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::update()
{
	dx=std::cos(angle*DEGTORAD)*6;
	dy=std::sin(angle*DEGTORAD)*6;
	// angle+=rand()%7-3;  /*try this*/
	x+=dx;
	y+=dy;

	if (x>W || x<0 || y>H || y<0) life=0;
}

