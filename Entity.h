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
protected:
	std::string name;
	inline void __setVelocity(float new_dx, float new_dy){
		dx = new_dx;
		dy = new_dy;
	}

public:
	float x,y,dx,dy,R,angle;
	bool life;
	Animation anim;

	Entity();

	virtual ~Entity();

	void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);

	virtual void update();

	void draw(sf::RenderWindow &app);

	bool collidesWith(const Entity *that) const;
	const Animation& getAnim() const;
	bool isAlive() const;
	void setLife(bool life);
	const std::string& getName() const;
};


#endif /* ENTITY_H_ */
