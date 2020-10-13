#include "Common.h"
#include "Animation.h"
#include "Entity.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Explosion.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <list>
#include <cmath>
#include <cstdlib>
#include <memory>
using namespace sf;


int main()
{
	std::srand(std::time(0));

	RenderWindow app(VideoMode(W, H), "Asteroids!");
	app.setFramerateLimit(60);

	Texture t1,t2,t3,t4,t5,t6,t7;
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite background(t2);

	Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
	Animation sRock(t4, 0,0,64,64, 16, 0.2);
	Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
	Animation sBullet(t5, 0,0,32,64, 16, 0.8);
	Animation sPlayer(t1, 40,0,40,40, 1, 0);
	Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
	Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


	std::list<std::shared_ptr<Entity>> entities;

	for(int i=0;i<15;i++)
	{
		std::shared_ptr<Asteroid> a = std::make_shared<Asteroid>();
		a->settings(sRock, rand()%W, rand()%H, rand()%360, 25.0);
		entities.push_back(a);
	}

	std::shared_ptr <Player> p = std::make_shared <Player>();
	p->settings(sPlayer,200,200,0,20);
	entities.push_back(p);

	/////main loop/////
	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
				{
					std::shared_ptr <Bullet> b = std::make_shared <Bullet>();
					b->settings(sBullet, p->x, p->y, p->angle,10.0);
					entities.push_back(b);
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3.0;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3.0;
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
		else p->thrust=false;


		for(auto a:entities)
			for(auto b:entities)
			{
				if (a->getName()=="asteroid" && b->getName()=="bullet")
					if ( a->collidesWith(*b) )
					{
						a->setLife(false);
						b->setLife(false);

						std::shared_ptr <Explosion> e = std::make_shared<Explosion>();
						e->settings(sExplosion,a->x,a->y);
						entities.push_back(e);


						for(int i=0;i<2;i++)
						{
							if (a->R==15) continue;
							std::shared_ptr<Asteroid> a = std::make_shared<Asteroid>();
							e->settings(sRock_small, a->x, a->y, rand()%360, 15.0);
							entities.push_back(e);
						}

					}

				if (a->getName()=="player" && b->getName()=="asteroid")
					if ( a->collidesWith(*b) )
					{
						b->setLife(false);

						std::shared_ptr <Explosion> e = std::make_shared<Explosion>();
						e->settings(sExplosion_ship, a->x, a->y);
						entities.push_back(e);

						p->settings(sPlayer, W/2, H/2, 0, 20.0);
						p->dx=0; p->dy=0;
					}
			}


		if (p->thrust)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;


		for(auto e:entities)
			if (e->getName()=="explosion")
				if (e->anim.isEnd()) e->setLife(false);

		if (rand()%150==0)
		{
			std::shared_ptr<Asteroid> a = std::make_shared<Asteroid>();
			a->settings(sRock, 0,rand()%H, rand()%360, 25.0);
			entities.push_back(a);
		}

		for(auto i=entities.begin();i!=entities.end();)
		{
			std::shared_ptr <Entity> e = *i;

			e->update();
			e->anim.update();

			if (e->isAlive()==false) {i=entities.erase(i);}
			else i++;
		}

		//////draw//////
		app.draw(background);
		for(auto i:entities) i->draw(app);
		app.display();
	}

	return 0;
}
