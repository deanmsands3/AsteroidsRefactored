#include "Game.h"
#include "Common.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <list>
#include <cmath>
#include <cstdlib>
#include <string>
#include <memory>


using json = nlohmann::json;

Game::Game(const std::string &json_file):_window(sf::VideoMode(W, H), "Asteroids!")
{
	std::srand(std::time(0));

	_window.setFramerateLimit(60);
	json index = loadJSON(json_file);
	loadTextures(index);
	loadAnimations(index);




}

Game::~Game()
{
    //dtor
}

void Game::play(){

	setup();
	loop();
	cleanup();
}

void Game::setup(){

}
void Game::loop(){
	/////main loop/////
	while (_window.isOpen())
	{
		innerLoop();
	}
}

void Game::innerLoop(){
	handleInput();
	gameLogic();
	updateEntities();
	cleanupEntities();
	draw();
}

void Game::handleInput(){

}

void Game::gameLogic(){

}


void Game::cleanup(){

}

void Game::addEntity(unsigned long long entity_id, std::shared_ptr<Entity> entity){
	_entities[entity_id] = entity;
}

void Game::delEntity(unsigned long long entity_id){
	_entities.erase(entity_id);
}

json Game::loadJSON(const std::string &json_file){
    json index;
	{
        std::ifstream index_file(json_file);
		index_file>>index;
	}
	return index;
}

void Game::loadTextures(const json &index){
    auto index_textures = index["Textures"];
    for(auto& [key, value]: index_textures.items() ){
    	std::string file_name = value.get<std::string>();
        std::cout << key << ":" << file_name << std::endl;
        sf::Texture t;
        t.loadFromFile(file_name);
        _textures[key] = t;
    }
}

void Game::loadAnimations(const json &index){
    auto index_animations = index["Animations"];
    for(auto& [key, value]: index_animations.items() ){
        auto texture_name = value["texture"].get<std::string>();
        sf::Texture t = _textures[texture_name];
        unsigned int x = value["x"].get<unsigned int>();
        unsigned int y = value["y"].get<unsigned int>();
        unsigned int w = value["w"].get<unsigned int>();
        unsigned int h = value["h"].get<unsigned int>();
        unsigned int frame_count = value["count"].get<unsigned int>();
        float speed = value["speed"].get<float>();
        Animation anim(t,x,y,w,h,frame_count, speed);
        _animations[key] = anim;
    }
}

void Game::loadEntities(const json &index){

}

void Game::draw(){
	for(auto i:_entities){
		i.second->draw(_window);
	}
	_window.display();
}

void Game::updateEntities(){
	for(auto i=_entities.begin();i!=_entities.end();){
		std::shared_ptr <Entity> e = i->second;

		e->update();
		e->anim.update();
	}
}

void Game::cleanupEntities(){
	for(auto i=_entities.begin();i!=_entities.end();){
		std::shared_ptr <Entity> e = i->second;
		if (e->isAlive()==false) {i=_entities.erase(i);}
		else i++;
	}
}
/** Access _textures
 * \return The current value of _textures
 */
sf::Texture Game::getTexture(const std::string &texture_name) { return _textures[texture_name]; }

/** Set _textures
 * \param val New value to set
 */
void Game::setTexture(std::string texture_name, const sf::Texture &val) { _textures[texture_name] = val; }

/** Access _animations
 * \return The current value of _animations
 */
Animation Game::getAnimation(std::string animation_name) { return _animations[animation_name]; }

/** Set _animations
 * \param val New value to set
 */
void Game::setAnimation(std::string animation_name, const Animation &val) { _animations[animation_name] = val; }

/** Access _entities
 * \return The current value of _entities
 */
std::shared_ptr<Entity> Game::getEntity(unsigned long long entity_id) {
	return _entities[entity_id];
}

/** Set _entities
 * \param val New value to set
 */
void Game::setEntity(unsigned long long entity_id, std::shared_ptr<Entity> val) { _entities[entity_id] = val; }
