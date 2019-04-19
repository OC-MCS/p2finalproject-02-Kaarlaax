#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "GlobalConstants.h"

class Bomb
{
	Sprite BombSprite; //this is the sprite that bombTexture will be assigned to

public:
	//constructor
	//set texture to bomb sprite
	//Parameters: Vector2f position of bomb, Texture passed by reference
	Bomb(Vector2f pos, Texture &BombTexture)
	{
		//set texture to sprite
		BombSprite.setTexture(BombTexture);
		BombSprite.setPosition(pos);
	}
	//draws one bomb
	//Parameters
	void drawBomb(RenderWindow &window)
	{
		window.draw(BombSprite);
	}
	void moveBomb()
	{
		const float DIST = 5.0f; //(will move 5 pixles every 60th of a second)
		BombSprite.move(0, DIST); //move it down in the y direction
	}
	bool isBombOnScreen()
	{
		bool onScreen = false;
		if (BombSprite.getPosition().y < WINDOW_HEIGHT)  //missile is on screen //WHAT IS A WAY TO GET WINDOW_HEIGHT FROM MAIN WITHOUT PASSING?
		{
			onScreen = true;
		}

		return onScreen;
	}
	FloatRect getGlobalBounds()
	{
		return BombSprite.getGlobalBounds();
	}
};
