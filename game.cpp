#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "game.h"
#include "glutapp.h"



game::game(void)
{
}


game::~game(void)
{
}


void game::initialize() {
	score = 0;
	for (int i = 0; i < 20; i++ ){
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				lines[i][j][k] = new tetrisBlock(false);
			}
		}
	}

	shpu = 19;
	shpv = 3;
	shpw = 3;
	currentShape = new tetrisShape(TSHP_L1);
	spawnNextShape();
	key_camup = false;
	key_camdown = false;
	key_camleft = false;
	key_camright = false;
	key_moveup = false;
	key_moveback = false;
	key_moveleft = false;
	key_moveright = false;
	key_rotright = false;
	key_rotleft = false;
	key_rotup = false;
	key_rotdown = false;
	key_rotspnleft = false;
	key_rotspnright = false;
	key_drop = false;

	gamestate = STATE_NORMAL;
	camrot = 25;

	droptick = 0;
	droptickrate = 1/30.0;
	movetick = 0;
	movetickrate = 10.0/30.0;
	rottick = 0;
	rottickrate = 7.0/30.0;
	

	/*lines[0][0][0]->isActive = true;
	lines[1][0][0]->isActive = true;
	lines[0][9][0]->isActive = true;
	lines[0][0][9]->isActive = true;
	lines[0][9][9]->isActive = true;*/
	for (int j = 0; j < 10; j++) {
		for (int k = 0; k < 10; k++) {
			lines[0][j][k]->isActive = true;
		}
	}

	lines[0][3][0]->isActive = false;
}

void game::update() {
	//update the cam pos
	double camincr = 0.7;
	
	if (key_camup && App->camY < 23.0) {
		App->camY += camincr;
	}
	if (key_camdown && App->camY > 5.0) {
		App->camY -= camincr;
	}
	if (key_camleft && App->camRot > -75.0) {
		App->camRot -= 5*camincr;
	}
	if (key_camright && App->camRot < 75.0) {
		App->camRot += 5*camincr;
	}

	if (gamestate == STATE_NORMAL) {
		//Update Falling block position
		droptick += droptickrate;
		if (droptick >= 1.0) {
			//drop block down by one
			if (checkNewShapePos(shpu-1,shpv,shpw)) {
				shpu--;
			} else {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							if (currentShape->blocks[i][j][k]->isActive) {
								int tu = i + shpu;
								int tv = j + shpv;
								int tw = k + shpw;
								if (tu > 19) {
									printf("Game Over!");
									//GAME OVERRRR
									gamestate = STATE_GAME_OVER;
									goto skip;
								}
								lines[tu][tv][tw]->isActive = true;
								lines[tu][tv][tw]->texidx = currentShape->texid;
							}
						}
					}
				}
				spawnNextShape();
			}

			droptick -= 1.0;
		}

		//int ut,vt,wt;
		//Apply player controls
		movetick += movetickrate;
		if (movetick >= 1.0) {
			if (key_moveup) {
				if (checkNewShapePos(shpu,shpv,shpw+1)) {
					shpw += 1;
					movetick = 0.0;
				}
			}
			if (key_moveback) {
				if (checkNewShapePos(shpu,shpv,shpw-1)) {
					shpw -= 1;
					movetick = 0.0;
				}
			}
			if (key_moveleft) {
				if (checkNewShapePos(shpu,shpv-1,shpw)) {
					shpv -= 1;
					movetick = 0.0;
				}
			}
			if (key_moveright) {
				if (checkNewShapePos(shpu,shpv+1,shpw)) {
					shpv += 1;
					movetick = 0.0;
				}
			}
			if (key_drop) {
				if (checkNewShapePos(shpu-1,shpv,shpw)) {
					shpu -= 1;
					movetick = 0.0;
				}
			}
		
		}

		rottick += rottickrate;
		if (rottick >= 1.0) {
			if (key_rotright) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[j][3-i][k];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}

			if (key_rotleft) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[3-j][i][k];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}

			if (key_rotup) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[k][j][3-i];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}

			if (key_rotdown) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[3-k][j][i];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}
			if (key_rotspnleft) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[i][k][3-j];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}
			if (key_rotspnright) {
				// rotate the matrix
				tetrisShape* s = new tetrisShape(currentShape->type, currentShape->texid);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						for (int k = 0; k < 4; k++) {
							s->blocks[i][j][k] = currentShape->blocks[i][3-k][j];
						}
					}
				}
				if (checkNewShapePos(s)) {
					currentShape = s;
					rottick = 0.0;
				}
			}
		}

		//Check for clear lines
		for (int i = 0; i < 20; i++) {
			int sum = 0;
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					if (lines[i][j][k]->isActive) {
						++sum;
					}
				}
			}
			if (sum == 100) {
				clearAndDropLine(i);
			}
		}
	}
skip:
	if (gamestate == STATE_GAME_OVER) {
		//something
	}

}

void game::spawnNextShape() {
	int randtype = (rand() % 7) + 1;
	//printf("Randomed: %d",randtype);
	tetrisShape* s = new tetrisShape(randtype);
	delete(currentShape);
	currentShape = s;
	shpu = 19;
	shpv = 3;
	shpw = 3;

}

void game::clearAndDropLine(int ln) {
	for (int i = ln; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					//clear line, then drop line above down one
					if (i != 19) {
						lines[i][j][k]->isActive = lines[i+1][j][k]->isActive;
						lines[i][j][k]->texidx = lines[i+1][j][k]->texidx;
					} else {
						lines[i][j][k]->isActive = false;
					}
				}
			}
	}


}

bool game::checkNewShapePos(int u, int v, int w) {
	//u = height
	//v = left/right
	//w = forward/back
	//0,0,0 is bottom left (-x, +z)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int tu,tv,tw;
				tu = i + u;
				tv = j + v;
				tw = k + w;
				bool blockstate = currentShape->blocks[i][j][k]->isActive;
				if (blockstate) {
					if (tu < 0) return false;
					if (tv < 0 || tv > 9) return false;
					if (tw < 0 || tw > 9) return false;
					if (tu > 19) continue;
					if (lines[tu][tv][tw]->isActive) {
						return false;
					}


				}
			}
		}
	}
	return true;
}
bool game::checkNewShapePos(tetrisShape* s) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int tu,tv,tw;
				tu = i + shpu;
				tv = j + shpv;
				tw = k + shpw;
				bool blockstate = s->blocks[i][j][k]->isActive;
				if (blockstate) {
					if (tu < 0 || tu > 19) return false;
					if (tv < 0 || tv > 9) return false;
					if (tw < 0 || tw > 9) return false;
					if (lines[tu][tv][tw]->isActive) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void game::display() {
	double xzero, zzero, yzero;
	xzero = -4.5 * BLOCK_SIZE;
	zzero = 4.5 * BLOCK_SIZE;
	yzero = 0.5 * BLOCK_SIZE;
	for (int i = 0; i < 20; i++ ){
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				if (lines[i][j][k]->isActive) {
					//display blocks on the field
					glPushMatrix();
					glTranslated(xzero + (j * BLOCK_SIZE), yzero + (i * BLOCK_SIZE), zzero - (k * BLOCK_SIZE));
					(*lines[i][j][k]).display();
					glPopMatrix();
				}
			}
		}
	}

	//display blocks in currently falling shape
	glPushMatrix();
	glTranslated(xzero + (shpv * BLOCK_SIZE), yzero + (shpu * BLOCK_SIZE), zzero - (shpw * BLOCK_SIZE));
	currentShape->display();
	glPopMatrix();


	//display grid lines
	glColor4d(0.4, 0.4, 0.4, 0.8);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_LINE_STIPPLE);
	unsigned char b = 0x000F;
	//glLineStipple(1, b);
	glBegin(GL_LINES);
	

	//vertical
	for (int i = 0; i <= 10; i+=1) {
		for (int j = 0; j <= 10; j+=1) {
			if ((i%10 == 0 && j%2 == 0)) {
				double xzero = -5 * BLOCK_SIZE;
				double zzero = 5 * BLOCK_SIZE;
				glVertex3d(xzero + i*BLOCK_SIZE, 0.0,zzero - j*BLOCK_SIZE);
				glVertex3d(xzero + i*BLOCK_SIZE, BLOCK_SIZE * 20,zzero - j*BLOCK_SIZE);
			}
		}
	}
	//left-right
	for (int i = 0; i <= 20; i+=1) {
		for (int j = 0; j <= 10; j+=1) {
			if ((isBottomOfShape(i) || i%20 == 0) && j%1 == 0) {
				double zzero = 5 * BLOCK_SIZE;
				glVertex3d(-5 * BLOCK_SIZE, i * BLOCK_SIZE, zzero - j*BLOCK_SIZE);
				glVertex3d(5 * BLOCK_SIZE, i * BLOCK_SIZE, zzero - j*BLOCK_SIZE);
			}
		}
	}

	//front-back
	for (int i = 0; i <= 20; i+=1) {
		for (int j = 0; j <= 10; j+=1) {
			if ((isBottomOfShape(i) || i%20 == 0) && j%1 == 0) {
				double xzero = -5 * BLOCK_SIZE;
				glVertex3d(xzero + j*BLOCK_SIZE, i * BLOCK_SIZE, 5 * BLOCK_SIZE);
				glVertex3d(xzero + j*BLOCK_SIZE, i * BLOCK_SIZE,-5 * BLOCK_SIZE);
			}
		}
	}

	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_LINE_STIPPLE);
}

bool game::isBottomOfShape(int ln) {
	int btm;
	for (int i = 0; i < 4; i++ ){
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (currentShape->blocks[i][j][k]->isActive) {
					btm = i;
					goto after;
				}
			}
		}
	}
after:
	if (ln == (btm + shpu)) {
		return true;
	} else {
		return false;
	}
}
