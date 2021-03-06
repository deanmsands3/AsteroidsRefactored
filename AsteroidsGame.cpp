#include "AsteroidsGame.h"
#include <iostream>

AsteroidsGame::AsteroidsGame(const std::string &json_file):Game(json_file) {
	//std::cout<<"Entering AsteroidsGame"<<std::endl;
	//Sprite background(t2);
    //background=sf::Sprite(getTexture("background"));
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);
    background.setTexture(t2);

	sExplosion=Animation(t3, 0,0,256,256, 48, 0.5);
	sRock=Animation(t4, 0,0,64,64, 16, 0.2);
	sRock_small=Animation(t6, 0,0,64,64, 16, 0.2);
	sBullet=Animation(t5, 0,0,32,64, 16, 0.8);
	sPlayer=Animation(t1, 40,0,40,40, 1, 0);
	sPlayer_go=Animation(t1, 40,40,40,40, 1, 0);
	sExplosion_ship=Animation(t7, 0,0,192,192, 64, 0.5);

	//std::cout<<"Leaving AsteroidsGame"<<std::endl;
}

AsteroidsGame::~AsteroidsGame() {
}

void AsteroidsGame::play() {
	//std::cout<<"Entering AsteroidsGame::play"<<std::endl;
	setup();
	loop();
	cleanup();
	//std::cout<<"Leaving AsteroidsGame::play"<<std::endl;

}

void AsteroidsGame::innerLoop() {
	handleInput();
	gameLogic();
	updateEntities();
	cleanupEntities();
	draw();
}

void AsteroidsGame::handleInput() {
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Space)
			{
				addBullet(_player->x, _player->y, _player->angle);
			}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _player->angle += 3.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  _player->angle -= 3.0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) _player->thrust=true;
	else _player->thrust=false;
}

void AsteroidsGame::gameLogic() {
	for(auto ast:_asteroids){
		auto asteroid = ast.second;

		for(auto bull:_bullets){
			auto bullet = bull.second;
			if ( asteroid->collidesWith(*bullet) )
			{
				asteroid->setLife(false);
				bullet->setLife(false);

				addExplosion(asteroid->x, asteroid->y);


				if (asteroid->R!=15){
					addSmallAsteroid(asteroid->x, asteroid->y);
					addSmallAsteroid(asteroid->x, asteroid->y);
				}
			}
		}
		if ( asteroid->collidesWith(*_player) )
		{
			asteroid->setLife(false);

			addExplosion(asteroid->x, asteroid->y);

			_player->settings(sPlayer, W/2, H/2, 0, 20.0);
			_player->dx=0; _player->dy=0;
		}


	}


	if (_player->thrust)  _player->anim = sPlayer_go;
	else   _player->anim = sPlayer;


	for(auto e:_explosions){
		auto explosion = e.second;
		if (explosion->anim.isEnd()) explosion->setLife(false);

	}

	if (rand()%150==0)
	{
		addBigAsteroid(rand()%W, rand()%H);
	}

}

void AsteroidsGame::updateEntities() {
	for(auto ent:_entities){
		std::shared_ptr <Entity> entity = ent.second;

		entity->update();
		entity->anim.update();
	}
}

void AsteroidsGame::cleanupEntities() {
	cleanupAsteroids();
	cleanupBullets();
	cleanupExplosions();
}

void AsteroidsGame::cleanupAsteroids() {
	//std::cout<<"cleaning up asteroids"<<std::endl;
	std::vector<unsigned long long> ids;
	for(auto iter:_asteroids){
		std::shared_ptr <Asteroid> ast = iter.second;
		if (ast->isAlive()==false) {
			auto id = iter.first;
			ids.push_back(id);
		}
	}
	for(auto id:ids){
		delAsteroid(id);
	}
}

void AsteroidsGame::cleanupBullets() {
	//std::cout<<"cleaning up bullets"<<std::endl;
	std::vector<unsigned long long> ids;
	for(auto iter:_bullets){
		std::shared_ptr <Bullet> bull = iter.second;
		if (bull->isAlive()==false) {
			auto id = iter.first;
			ids.push_back(id);
		}
	}
	for(auto id:ids){
		delBullet(id);
	}
}

void AsteroidsGame::cleanupExplosions() {
	//std::cout<<"cleaning up explosions"<<std::endl;
	std::vector<unsigned long long> ids;
	for(auto iter:_explosions){
		std::shared_ptr <Explosion> e = iter.second;
		auto id = iter.first;
		if (e->isAlive()==false) {
			ids.push_back(id);
		}
	}
	for(auto id:ids){
		delExplosion(id);
	}
}



void AsteroidsGame::draw(){
	_window.draw(background);
	Game::draw();
}



void AsteroidsGame::addPlayer(unsigned x, unsigned y){
	_player = std::make_shared <Player>();
	_player->settings(sPlayer, x, y, 0, 20);
	unsigned long long id = (unsigned long long)_player.get();
	addEntity(id, _player);
}

void AsteroidsGame::addBigAsteroid(unsigned x, unsigned y){
	std::shared_ptr<Asteroid> a = std::make_shared<Asteroid>();
	a->settings(sRock, x, y, rand()%360, 25.0);
	addAsteroid(a);
}
void AsteroidsGame::addSmallAsteroid(unsigned x, unsigned y) {
	std::shared_ptr<Asteroid> a = std::make_shared<Asteroid>();
	a->settings(sRock_small, x, y, rand()%360, 15.0);
	addAsteroid(a);
}

void AsteroidsGame::addAsteroid(std::shared_ptr<Asteroid> asteroid){
	unsigned long long id = (unsigned long long)asteroid.get();
	_asteroids[id] = asteroid;
	addEntity(id, asteroid);
}

void AsteroidsGame::delAsteroid(unsigned long long id) {
	_asteroids.erase(id);
	delEntity(id);
}

void AsteroidsGame::addBullet(unsigned x, unsigned y, float angle){
	std::shared_ptr <Bullet> bullet = std::make_shared <Bullet>();
	unsigned long long id = (unsigned long long)bullet.get();
	bullet->settings(sBullet, x, y, angle,10.0);
	_bullets[id] = bullet;
	addEntity(id, bullet);
}

void AsteroidsGame::delBullet(unsigned long long id) {
	_bullets.erase(id);
	delEntity(id);
}

void AsteroidsGame::addExplosion(unsigned x, unsigned y) {
	std::shared_ptr <Explosion> explosion = std::make_shared <Explosion>();
	unsigned long long id = (unsigned long long)explosion.get();
	explosion->settings(sExplosion, x, y);
	_explosions[id] = explosion;
	addEntity(id, explosion);
}

void AsteroidsGame::delExplosion(unsigned long long id) {
	_explosions.erase(id);
	delEntity(id);
}

void AsteroidsGame::setup(){
	for(int i=0;i<15;i++){
		addBigAsteroid(rand()%W, rand()%H);
	}

	addPlayer(200, 200);
}

void AsteroidsGame::loop() {
	/////main loop/////
	while (_window.isOpen())
	{
		innerLoop();
	}
}

void AsteroidsGame::cleanup(){

}
