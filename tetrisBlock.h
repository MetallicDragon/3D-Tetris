/*
	This will be the base "blocks" in the game. Shapes will be made of these, and the structure of placed blocks too.
*/

#pragma once
#define BLOCK_SIZE 1.0
class tetrisBlock
{
public:
	tetrisBlock(void);
	~tetrisBlock(void);
	tetrisBlock(bool state);
	tetrisBlock(bool state, int tid);
	void display();
	void display(int tid);




	//int x,y,z; //this block's coordinates in terms of the grid space
	bool isActive; //true if there is actually a block here
	int texidx; //texture index

};

