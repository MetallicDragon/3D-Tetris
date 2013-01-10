#include "tetrisBlock.h"
#include "glutapp.h"



tetrisBlock::tetrisBlock(void)
{
	isActive = false;
	texidx = 0;
}


tetrisBlock::~tetrisBlock(void)
{
}

tetrisBlock::tetrisBlock(bool state) {
	this->isActive = state;
	texidx = 0;
}



void tetrisBlock::display(int tid) {
	//assumes caller handles translations
	glColor3d(1.0, 1.0, 1.0);
	double s = BLOCK_SIZE/2;
	int tex = App->texture[tid];

	//glutSolidCube(BLOCK_SIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBegin( GL_QUADS );

	glNormal3d(0.0,0.0,1.0);
	glTexCoord2d(0.0,0.0); glVertex3d(-s, -s, s);//front cube face
	glTexCoord2d(0.0,1.0); glVertex3d(-s,s,s);
	glTexCoord2d(1.0,1.0); glVertex3d(s,s,s);
	glTexCoord2d(1.0,0.0); glVertex3d(s,-s,s);
	
	glNormal3d(0.0,0.0,-1.0);
	glTexCoord2d(0.0,0.0); glVertex3d(-s, -s, -s);//back
	glTexCoord2d(0.0,1.0); glVertex3d(-s,s,-s);
	glTexCoord2d(1.0,1.0); glVertex3d(s,s,-s);
	glTexCoord2d(1.0,0.0); glVertex3d(s,-s,-s);

	glNormal3d(-1.0,0.0,0.0);
	glTexCoord2d(0.0,0.0); glVertex3d(-s, -s, -s);//left
	glTexCoord2d(0.0,1.0); glVertex3d(-s,s,-s);
	glTexCoord2d(1.0,1.0); glVertex3d(-s,s,s);
	glTexCoord2d(1.0,0.0); glVertex3d(-s,-s,s);

	glNormal3d(1.0,0.0,0.0);
	glTexCoord2d(0.0,0.0); glVertex3d(s, -s, -s);//right
	glTexCoord2d(0.0,1.0); glVertex3d(s,s,-s);
	glTexCoord2d(1.0,1.0); glVertex3d(s,s,s);
	glTexCoord2d(1.0,0.0); glVertex3d(s,-s,s);

	glNormal3d(0.0,1.0,0.0);
	glTexCoord2d(0.0,0.0); glVertex3d(-s, s, s);//top
	glTexCoord2d(0.0,1.0); glVertex3d(-s,s,-s);
	glTexCoord2d(1.0,1.0); glVertex3d(s,s,-s);
	glTexCoord2d(1.0,0.0); glVertex3d(s,s,s);

	glNormal3d(0.0,-1.0,0.0);
	glTexCoord2d(0.0,0.0); glVertex3d(-s, -s, s);//bottom
	glTexCoord2d(0.0,1.0); glVertex3d(-s,-s,-s);
	glTexCoord2d(1.0,1.0); glVertex3d(s,-s,-s);
	glTexCoord2d(1.0,0.0); glVertex3d(s,-s,s);


	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

void tetrisBlock::display() {
	display(texidx);
}
