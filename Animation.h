/*
 * Animation.h
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
   public:
   float Frame, speed;
   sf::Sprite sprite;
   std::vector<sf::IntRect> frames;

   Animation();

   Animation (sf::Texture &t, int x, int y, int w, int h, int count, float Speed);

   virtual ~Animation();

   void update();

   bool isEnd();

};


#endif /* ANIMATION_H_ */
