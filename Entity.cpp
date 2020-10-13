/*
 * Entity.cpp
 *
 *  Created on: Oct 7, 2020
 *      Author: dean
 */
#include "Entity.h"


Entity::Entity(){
	life=1;
}

Entity::~Entity(){};

void Entity::settings(Animation &a,int X,int Y,float Angle, float radius){
	anim = a;
	x=X; y=Y;
	angle = Angle;
	R = radius;
}

void Entity::update(){};

void Entity::draw(sf::RenderWindow &app){
	anim.sprite.setPosition(x,y);
	anim.sprite.setRotation(angle+90);
	app.draw(anim.sprite);

	sf::CircleShape circle(R);
	circle.setFillColor(sf::Color(255,0,0,170));
	circle.setPosition(x,y);
	circle.setOrigin(R,R);
	//app.draw(circle);
}

bool Entity::collidesWith(const Entity &that) const{
	return (
		(that.x - x)*(that.x - x)+
		(that.y - y)*(that.y - y)<
		(that.R + R)*(that.R + R)
	);
}

const Animation& Entity::getAnim() const {
	return anim;
}

bool Entity::isAlive() const {
	return life;
}

void Entity::setLife(bool life) {
	this->life = life;
}

const std::string& Entity::getName() const {
	return name;
}
