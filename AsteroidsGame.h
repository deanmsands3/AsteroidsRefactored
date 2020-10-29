#ifndef ASTEROIDSGAME_H
#define ASTEROIDSGAME_H
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Explosion.h"
#include "Game.h"

class AsteroidsGame: public Game{
    std::unordered_map<unsigned long long, std::shared_ptr<Asteroid> > _asteroids; //!< Member variable "_asteroids"
    std::unordered_map<unsigned long long, std::shared_ptr<Bullet> > _bullets; //!< Member variable "_bullets"
    std::unordered_map<unsigned long long, std::shared_ptr<Explosion> > _explosions; //!< Member variable "_explosions"
    std::shared_ptr<Player> _player;
    sf::Sprite background;
	sf::Texture t1,t2,t3,t4,t5,t6,t7;
	Animation sExplosion, sRock, sRock_small, sBullet, sPlayer, sPlayer_go, sExplosion_ship;
	void cleanupAsteroids();
	void cleanupBullets();
	void cleanupExplosions();
protected:
    virtual void setup();
    virtual void loop();
    virtual void innerLoop();
    virtual void handleInput();
    virtual void gameLogic();
    virtual void updateEntities();
    virtual void cleanupEntities();
    virtual void cleanup();
    virtual void draw();
public:
	AsteroidsGame(const std::string &json_file);
	~AsteroidsGame();
	virtual void play();
	void addPlayer(unsigned x, unsigned y);
	void addAsteroid(std::shared_ptr<Asteroid> asteroid);
	void addBigAsteroid(unsigned x, unsigned y);
	void addSmallAsteroid(unsigned x, unsigned y);
	void delAsteroid(unsigned long long id);
	void addBullet(unsigned x, unsigned y, float angle);
	void delBullet(unsigned long long id);
	void addExplosion(unsigned x, unsigned y);
	void delExplosion(unsigned long long id);

};

#endif
