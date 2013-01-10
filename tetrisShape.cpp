
#include <stdlib.h>
#include "tetrisShape.h"
#include "glutapp.h"


tetrisShape::tetrisShape(void)
{
	initializeWithType(TSHP_CUBE);
}


tetrisShape::~tetrisShape(void)
{
}

tetrisShape::tetrisShape(int t) {
	initializeWithType(t);
}

tetrisShape::tetrisShape(int t, int tid) {
	initializeWithType(t, tid);
}

void tetrisShape::display() {
	//assume caller centers correctly
	glColor3d(0.6, 0.6, 0.6);
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (blocks[i][j][k]->isActive) {
					glPushMatrix();
					glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, k * -1 * BLOCK_SIZE);
					blocks[i][j][k]->display(texid);
					glPopMatrix();
				}
			}
		}
	}

}

void tetrisShape::initializeWithType(int t) {
	initializeWithType(t, rand()%4);
}

void tetrisShape::initializeWithType(int t, int tid) {
	type = t;
	texid = tid;


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				blocks[i][j][k] = new tetrisBlock(false);
			}
		}
	}

	/*
	TSHP_LINE 1
	TSHP_CUBE 2
	TSHP_L1 3
	TSHP_L2 4
	TSHP_Z1 5
	TSHP_Z2 6
	TSHP_T 7
	*/
	if (type == TSHP_LINE) {
		for (int i = 0; i < 4; i++) {
			//1x4
			blocks[i][1][1]->isActive = true;
		}
	} else if (type == TSHP_CUBE) {
		//2x2 in center
		blocks[1][1][1]->isActive = true;
		blocks[1][2][1]->isActive = true;
		blocks[1][1][2]->isActive = true;
		blocks[1][2][2]->isActive = true;
		blocks[2][1][1]->isActive = true;
		blocks[2][2][1]->isActive = true;
		blocks[2][1][2]->isActive = true;
		blocks[2][2][2]->isActive = true;
	} else if (type == TSHP_L1) {
		//3x1 + 1x2 on tip
		for (int i = 1; i < 4; i++) {
			//3x1 part
			blocks[i][1][1]->isActive = true;
		}
		blocks[3][1][2]->isActive = true;
		//blocks[3][2][2]->isActive = true;
	} else if (type == TSHP_L2) {
		//3x1 + 1x2 on tip, reversed 
		for (int i = 1; i < 4; i++) {
			//3x1 part
			blocks[i][2][1]->isActive = true;
		}
		//blocks[3][1][2]->isActive = true;
		blocks[3][2][2]->isActive = true;
	} else if (type == TSHP_Z1) {
		//blocks[2][1][1]->isActive = true;
		blocks[2][1][2]->isActive = true;
		blocks[2][2][2]->isActive = true;
		blocks[1][2][2]->isActive = true;
		blocks[1][3][2]->isActive = true;
		//blocks[1][3][3]->isActive = true;
	} else if (type == TSHP_Z2) {
		//blocks[2][1][3]->isActive = true;
		blocks[2][1][2]->isActive = true;
		blocks[2][2][2]->isActive = true;
		//blocks[1][3][1]->isActive = true;
		blocks[1][2][2]->isActive = true;
		blocks[1][3][2]->isActive = true;
	} else if  (type == TSHP_T) {
		//blocks[1][2][2]->isActive = true;
		blocks[2][2][2]->isActive = true;
		blocks[3][2][2]->isActive = true;
		blocks[2][1][2]->isActive = true;
		blocks[2][3][2]->isActive = true;
		//blocks[2][2][3]->isActive = true;
		//blocks[2][2][1]->isActive = true;
	}

	

}