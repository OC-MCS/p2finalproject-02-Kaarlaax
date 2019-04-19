#pragma once
#include <iostream>
using namespace std;

//these global constants are used in main and other classes as the size of the screen and the different screen states
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

enum GameStateEnum { WELCOME, LEVEL_ONE, LEVEL_TWO, ALIEN_WON, NAVEL_WON };
//welcome is the start screen 
//level one and two are with different aliens
//alien won displays when an alien wins the game
//navel won displays when a human wins the game