#pragma once
#include "tetrisShape.h"
#include "tetrisBlock.h"
#include "vec.h"

#define STATE_NORMAL 1
#define STATE_GAME_OVER 2

class game
{
public:
	game(void);
	~game(void);
	void initialize(); //initializes every variable to its starting values
	void update(); //Updates the game state by one "tick"
	void display(); //Displays everything that is part of the game
	bool checkNewShapePos(int u, int v, int w); //checks if a new position for the shape block would create collisions
	bool checkNewShapePos(tetrisShape* s);
	void spawnNextShape(); //spawns the next shape at the top of the arena
	void clearAndDropLine(int ln);
	bool isBottomOfShape(int ln);

	tetrisBlock *lines[20][10][10]; //These are the "lines" that make up the fallen blocks. Each "line" is a 10x10 square of "tetrisSquares".
	tetrisShape *currentShape;
	int shpu,shpv,shpw; //current shape's grid co-ords
	int score;
	int gamestate;
	double camrot;
	double droptick;
	double droptickrate;
	double movetick;
	double movetickrate;
	double rottick;
	double rottickrate;

	bool key_camup, key_camdown, key_camleft, key_camright;
	bool key_moveback, key_moveup, key_moveleft, key_moveright;
	bool key_rotright, key_rotleft, key_rotup, key_rotdown, key_rotspnleft, key_rotspnright;
	bool key_drop;
};

