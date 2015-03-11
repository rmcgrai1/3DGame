// Player.cpp


#include <deque>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <string>
#include <iostream>
#include "../IO/InputController.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Controller.h"
#include "Character.h"
#include "Player.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;


float nCDir = 0;

Player :: Player(float x, float y, float z) : Character(x,y,z) {
}

void Player :: update(Controller* c, float deltaTime) {

	Character :: update(c, deltaTime);

	// Update User Control of Player
	updateControl(c,deltaTime);



	/*glEnable(GL_LIGHT0);
	GLfloat lightpos[] = {x, y, z, 1};
	//GLfloat lightpos[] = {0,0,-1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);*/



	float len = 50, dir = nCDir;

	// Place Camera on Heightmap
		Heightmap* h = c->getHeightmap();
		float cX, cY;
		cX = x-calcLenX(len,nCDir);
		cY = y-calcLenY(len,nCDir);	

		c->getGraphicsOGL()->setProjectionPrep(cX,cY,h->getHeightXY(cX,cY)+8+10,x,y,z+8);
}

void Player :: draw(Controller* c, float deltaTime) {

	Character :: draw(c, deltaTime);
}

void Player :: updateControl(Controller* c, float deltaTime) {
	InputController* i = c->getInputController();
	float dir = i->getWASDDir(), cDir = gl->getCamDir(), aDir;
	aDir = dir-90;


	// If a Button is Held...
	if(dir != -1) {
		vel = 1 + i->getShift()*2;

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

		
		hop();
	}
	else
		vel = 0;
}

void Player :: land() {
}
