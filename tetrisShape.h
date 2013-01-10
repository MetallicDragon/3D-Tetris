//The falling shapes that a player manipulates
#include "tetrisBlock.h"

#pragma once

#define TSHP_LINE 1
#define TSHP_CUBE 2
#define TSHP_L1 3
#define TSHP_L2 4
#define TSHP_Z1 5
#define TSHP_Z2 6
#define TSHP_T 7
class tetrisShape
{
public:
	tetrisShape(void);
	~tetrisShape(void);
	tetrisShape(int t);
	tetrisShape(int t, int tid);
	void initialize();
	void initializeWithType(int t);
	void initializeWithType(int t, int tid);
	void update(); //update by one "tick"
	void display(); //displays all the blocks that are part of this shape

	tetrisBlock *blocks[4][4][4];
	int type;
	int texid;

};

