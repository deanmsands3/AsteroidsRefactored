/*
 * Asteroid.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#include "Asteroid.h"

Asteroid::Asteroid(){
  dx=rand()%8-4;
  dy=rand()%8-4;
  name="asteroid";
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}



void Asteroid::update(){
 x+=dx;
 y+=dy;

 if (x>W) x=0;  if (x<0) x=W;
 if (y>H) y=0;  if (y<0) y=H;
}
