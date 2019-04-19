//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
//#include <SFML/Graphics.hpp>
using namespace sf;
#include "GlobalConstants.h"
#include <time.h>
#include "Navel.h"
#include "Alien.h"
#include "ArmyAlien.h"
#include "Bullet.h"
#include "bulletClump.h"
#include "Bomb.h"
#include "BombClump.h"
#include "UI.h"

//============================================================
// YOUR HEADER WITH YOUR NAME GOES HERE. PLEASE DO NOT FORGET THIS
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

GameStateEnum resetState(int lives, int &destroyedAliens, GameStateEnum currentState, ArmyAlien &alienMafia, BulletClump &manyBullets, BombClump &manyBombs);


int main()
{
	srand(time(NULL)); //for random numbers later in loop
	int randNum;

	int lives = 5; //lives of human
	int destroyedAliens = 0; //number of aliens destroyed

	GameStateEnum currentState = BIENVENIDO; //this is from the "GlobalConstants.h", options include: WELCOME, LEVEL_ONE, LEVEL_TWO, ALIEN_WON, HUMAN_WON

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!"); //where I get my wonderful title from
	window.setFramerateLimit(60); //Limit the framerate to 60 frames per second

	//declare all instances of classes
	UI userInterface(window);
	Navel destroyer(window);
	ArmyAlien alienMafia;
	BulletClump manyBullets;
	BombClump manyBombs;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // "close requested" event: we close the window
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space) //handle space bar
				{
					manyBullets.newBullet(destroyer.getPosition()); //add a new bullet where the ship is located
				}
			}
			else if (event.type == Event::MouseButtonReleased) //handle mouse button pressed
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				if (userInterface.detectStart(mousePos)) //if they pressed one of the buttons to start the game
				{
					currentState = LEVEL_ONE;

					alienMafia.populateAlienList(currentState); //populate the alienArmy after pressing Start
				}
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where the
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		if (currentState == WELCOME) //if the enum state is welcome
		{
			cout << "in welcome screen " << endl; ///TESTING CODE
			userInterface.drawStartScreen(window); //draw the screen that belongs to welcome
		}
		else if (currentState == LEVEL_ONE || currentState == LEVEL_TWO) //if the enum state is level one or two
		{
			if (currentState == LEVEL_ONE) ///TESTING CODE
			{
				cout << "in level one " << endl;
			}
			else if (currentState == LEVEL_TWO) ///TESTING CODE
			{
				cout << "in level two " << endl;
			}

			userInterface.drawGameScreen(window, lives, destroyedAliens);//draw game labels

			if (destroyer.isNavelHitByAnyBombs(manyBombs.getBombList(), lives)) //if the ship is hit by any bombs
			{
				alienMafia.resetAliensPos(); //bring aliens to top
				destroyer.resetShipPos(window); //bring navel to center
				manyBullets.clearBullets(); //clear allbullets on screen 
				manyBombs.clearBombs(); //clear all bombs on screen
			}
			if (alienMafia.haveAliensReachedShip(lives)) //automatically resets the ship if reached by aliens
			{
				destroyer.resetShipPos(window);
				manyBullets.clearBullets(); //clear all missiles on screen 
				manyBombs.clearBombs(); //clear all bombs on screen
			}
			destroyer.moveNavel(window); //ship movement

			alienMafia.detectHitAliens(manyBullets.getBulletList(), destroyedAliens); //see who got hit
			alienMafia.moveAlienArmy(); //move aliens down

			manyBullets.moveBulletClump(); //move missiles up

			//add code here that makes the bombs faster for level 2
			if (currentState == LEVEL_ONE)
			{
				randNum = rand() % 60 - 1; //random new bombs (kind of slow)

			}
			else if (currentState == LEVEL_TWO)
			{
				randNum = rand() % 30 - 1; //random new bombs (kind of fast)
			}
			if (randNum == 3)
			{
				if (!alienMafia.isListEmpty())//make sure that the list of aliens has aliens in it before you make a bomb
				{
					Vector2f tempPos = alienMafia.getRandomAlienPos(window, destroyedAliens);
					manyBombs.newBomb(tempPos);
				}

			}
			manyBombs.moveBombClump(); //move bombs down

			//make everything appear
			destroyer.drawShip(window);
			alienMafia.drawAlienArmy(window);
			manyBullets.drawBulletClump(window);
			manyBombs.drawBombGroup(window);

			//chang the state of the game (if applicable)
			currentState = resetState(lives, destroyedAliens, currentState, alienMafia, manyBullets, manyBombs);
		}
		else if (currentState == ALIEN_WON) //if the aliens have taken all of the navals's lives
		{
			cout << "An alien won loop " << endl; ///TESTING CODE
			userInterface.drawWinnerScreen(window, "Alien"); //draw winner screen, saying the alien won

			alienMafia.clearAliens();//clear out list
			//reset the scores
			destroyedAliens = 0;
			lives = 5;

		}
		else if (currentState == NAVEL_WON) //if the human has taken all of the aliens' lives
		{
			cout << "in human won loop " << endl; ///TESTING CODE
			userInterface.drawWinnerScreen(window, "Human"); //draw winner screen, saying the human won

			alienMafia.clearAliens();//clear out list
			//reset the scores
			destroyedAliens = 0;
			lives = 5;
		}

		window.display(); //display everything that was drawn
	}

	return 0;
}


//look for winners
//reset current state of the enums if needed
GameStateEnum resetState(int lives, int &destroyedAliens, GameStateEnum currentState, ArmyAlien &alienMafia, BulletClump &manyMissiles, BombClump &manyBombs)
{
	if (lives == 0)
	{
		currentState = ALIEN_WON;
	}
	else if (destroyedAliens == 10)
	{
		if (currentState == LEVEL_TWO)
		{
			currentState = NAVEL_WON; //this line must not be working
		}
		else
		{
			currentState = LEVEL_TWO;
			//make changes for transitioning from level one to level two
			alienMafia.clearAliens();//clear out list
			manyMissiles.clearBullets(); //clear all missiles on screen 
			manyBombs.clearBombs(); //clear all bombs on screen
			alienMafia.populateAlienList(currentState);
			destroyedAliens = 0; //back to having hit no aliens
		}
	}
	return currentState;
}



