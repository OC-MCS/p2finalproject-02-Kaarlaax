#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
	Sprite bulletSprite;
public:
	//constructor
	Bullet(Vector2f pos, Texture &bulletTexture)
	{
		//set texture to sprite
		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setPosition(pos);
	}

	//draw one bullet
	//Parameters: RenderWindow&
	//Returns: void
	void drawMissile(RenderWindow &window)
	{
		window.draw(bulletSprite);
	}

	//move one bullet up screen
	//Parameters: none
	//Returns: void
	void moveMissile()
	{
		const float DIST = 5.0f; //(will move 5 pixles every 60th of a second)
		bulletSprite.move(0, -DIST); //move it up in the y direction
	}

	
	//Parameters: none
	//Returns: FloatRect (bullet bounds)
	FloatRect getGlobalBounds()
	{
		return bulletSprite.getGlobalBounds();
	}

	//check if bullet is on screen
	//Parameters: none
	//Returns: bool (is bullet on screen)
	bool isBulletOnScreen()
	{
		bool onScreen = false;
		if (bulletSprite.getPosition().y < 0)  //bullet is on screen
		{
			onScreen = true;
		}
		return onScreen;
	}

};
