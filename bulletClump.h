#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Bullet.h"
using namespace sf;

class BulletClump
{
	Texture bulletTexture;
	list<Bullet> multipleBullets; //list to keep track of missiles
public:
	//Constructor: load bullet texture
	BulletClump()
	{
		if (!bulletTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load Missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	
	//Parameters: Vector2f (position you want missile to be added at)
	//Returns: void
	void newBullet(Vector2f pos)
	{
		Bullet temp(pos, bulletTexture);
		multipleBullets.push_back(temp);
	}

	//draw list of missiles
	//Parameters: RenderWindow&
	//Returns: void
	void drawBulletClump(RenderWindow &window)
	{
		list<Bullet>::iterator iter;
		for (iter = multipleBullets.begin(); iter != multipleBullets.end(); iter++)
		{
			iter->drawMissile(window);
		}
	}

	//move list of missiles up the screen
	//Parameters: none
	//Returns: void
	void moveBulletClump()
	{
		//while there are lives left

		//move all aliens down the screen
		list<Bullet>::iterator iter;
		for (iter = multipleBullets.begin(); iter != multipleBullets.end(); iter++)
		{
			iter->moveMissile();
		}

	}

	//return list of missiles (to pass to other functions and see if the missiles hit anything)
	//Parameters: none
	//Returns: list<Missile>
	list<Bullet> &getBulletList()
	{
		return multipleBullets;
	}

	//clear out all missiles to start fresh
	//Parameters: none
	//Returns: void
	void clearBullets()
	{
		multipleBullets.clear();
	}
};
