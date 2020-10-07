/*
 * Asteroid.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_
#include "Entity.h"

class Asteroid: public Entity
{
   public:
   Asteroid();
   virtual ~Asteroid();

   void update();
};


#endif /* ASTEROID_H_ */
