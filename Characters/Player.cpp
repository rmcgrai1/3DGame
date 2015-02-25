// Player.cpp


#include <deque>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "Player.h"
#include "../Functions/Math2D.h"


float nCDir = 0, s = 6, h = 8;

Player :: Player(float x, float y, float z) : Physical(x,y,z) {
	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;
}

void Player :: update(GraphicsOGL* gl, float deltaTime) {
	Physical :: update(gl, deltaTime);

	updateControl(gl,deltaTime);


	float hopZVelP = hopZVel;

	hopZVel -= .2;
	hopZ += hopZVel;
	if(hopZ < 0) {
		hopZ = hopZVel = 0;

		if(hopZVelP != 0)
			hopSc *= 1.3;
	}

	hopSc += (1 - hopSc)/3;


	float len = 50, dir = nCDir;
	
	gl->setProjectionPrep(x-calcLenX(len,nCDir),y-calcLenY(len,nCDir),z+8+10,x,y,z+8);
}

void Player :: draw(GraphicsOGL* gl, float deltaTime) {
	Physical :: draw(gl, deltaTime);

	float sideNum = 4;
	float ang = 45, dir, xN, yN;

	glTranslatef(x,y,z+hopZ);
	glRotated(direction, 0, 0, 1);
	//gl.glRotated(rotY, 0, 1, 0);
	//gl.glRotated(rotX, 1, 0, 0);
	
	glScalef(hopSc,hopSc,1/hopSc);

	// Draw Top of Player Model
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2d(.5, .5);
			glVertex3d(0,0,h);

		for(int i = 0; i <= sideNum; i++) {
			dir = ang + i/sideNum*360;

			xN = calcLenX(1,dir);
			yN = calcLenY(1,dir);

			glTexCoord2d(.5 + .5*xN,.5 + .5*yN);
				glVertex3d(xN*s, yN*s, h);
		}
	glEnd();

	// Draw Side Faces of Player Model
	for(int i = 0; i < sideNum; i++) {
		glBegin(GL_QUADS);

			dir = ang + i/sideNum*360;
				xN = calcLenX(1,dir);
				yN = calcLenY(1,dir);

			glTexCoord2d(0,0);
				glVertex3d(xN*s, yN*s, h);
			glTexCoord2d(0,1);
				glVertex3d(xN*s, yN*s, 0);


			dir = ang + (i+1)/sideNum*360;
				xN = calcLenX(1,dir);
				yN = calcLenY(1,dir);

			glTexCoord2d(1,1);
				glVertex3d(xN*s, yN*s, 0);
			glTexCoord2d(1,0);
				glVertex3d(xN*s, yN*s, h);
		glEnd();
	}
	
	glLoadIdentity();
}

void Player :: updateControl(GraphicsOGL* gl, float deltaTime) {
	float dir = gl->getWASDDir(), cDir = gl->getCamDir(), aDir;
	aDir = dir-90;

	if(dir != -1) {
		vel = 1 + gl->getShift()*2;

		if(dir == 90 || dir == -90) {
			nCDir = cDir;
			direction = cDir - 90 + dir;	
		}
		else if(dir == 0 || dir == 180) {
			direction = cDir - 90 + dir;	
			nCDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else if(dir == 45 || dir == 135) {
			direction = cDir - 90 + dir;	
			nCDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else {
			direction = cDir - 90 + dir;	
			nCDir = cDir - .2*calcTurnToDir(cDir,180+cDir-90+dir);
		}

		
		if(hopZ == 0)
			hopZVel = 1.3;
	}
	else
		vel = 0;
}
