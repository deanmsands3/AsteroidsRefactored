/*
 * Entity.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#ifndef ENTITY_H_
#define ENTITY_H_
#include "Common.h"
#include "Animation.h"
#include <string>
#include <SFML/Graphics.hpp>

class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entity();

   virtual ~Entity();

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);

   virtual void update();

   void draw(sf::RenderWindow &app);
};


#endif /* ENTITY_H_ */
