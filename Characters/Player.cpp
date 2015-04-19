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
#include "../Primitives/Physical.h"
#include "Player.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;


float nCDir = 0;
float jumpSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*24));


Player :: Player(float x, float y, float z) : Character(x,y,z) {
	
	Player::camDis = 70;
}

void Player :: update(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("Player.cpp, update()");


	Character :: update(gl, deltaTime);

	// Update User Control of Player

	if(knockbackTimer == -1)
		updateControl(gl,deltaTime);



	/*glEnable(GL_LIGHT0);
	GLfloat lightpos[] = {x, y, z, 1};
	//GLfloat lightpos[] = {0,0,-1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);*/



	float dir = nCDir;

	// Place Camera on Heightmap
		Heightmap* h = gl->getHeightmap();
		float cX, cY;
		cX = x-calcLenX(camDis,nCDir);
		cY = y-calcLenY(camDis,nCDir);	

		if(target == NULL || !gl->getInputController()->checkLetter('q'))
			gl->setProjectionPrep(cX,cY,h->getHeightXY(cX,cY)+8+10,x,y,floorZ+8);
		else {
			float tS = targetShift*.1, toX, toY, toZ;
			toX = tS*(target->getX()) + (1-tS)*(x);
			toY = tS*(target->getY()) + (1-tS)*(y);
			toZ = floorZ+8;

			//direction = calcPtDir(x,y,target->getX(),target->getY());

			gl->setProjectionPrep(cX,cY,h->getHeightXY(cX,cY)+8+10,toX,toY,toZ);
		}
}

void Player :: draw(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("Player.cpp, draw()");

	Character :: draw(gl, deltaTime);
}

void Player :: updateControl(GraphicsOGL* gl, float deltaTime) {
	int PrevzState = 0;
	InputController* i = gl->getInputController();

	float dir = i->getWASDDir(), cDir = gl->getCamDir(), aDir, d;

	//flight
	/*int zState = i->checkLetter('z'); // get current state of the key
	if(zState && !PrevzState) { // if key just pressed down
		hopZVel += 0;
		zVel = 0;
		hopZ = 0;
		z += 10;
		floorZ = z;
		flight = !flight; // toggle
	}
	PrevzState = zState;*/ // record current key state in previous key state for next iteration


	aDir = dir-90;

	// If Jump Button Pressed...
	if(i->checkKey(' ')) {
		if(onGround) {
			zVel = jumpSpeed;
			onGround = false;
		}
	}
	else if(!onGround && zVel > 0) {
		zVel += (0 - zVel)/3;
	}

	// If a Button is Held...
	if(dir != -1) {
		isMoving = true;
		vel += ((1 + i->getShift()*2) - vel)/(3 + (vel > 1)*10);

		if(dir == 90 || dir == -90) {
			nCDir = cDir;
			d = cDir - 90 + dir;	
		}
		else if(dir == 0 || dir == 180) {
			d = cDir - 90 + dir;	
			nCDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else if(dir == 45 || dir == 135) {
			d = cDir - 90 + dir;	
			nCDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else {
			d = cDir - 90 + dir;	
			nCDir = cDir - .2*calcTurnToDir(cDir,180+cDir-90+dir);
		}

		direction = d;
		faceDirection(d);
	}
	else {
		vel += (0 - vel)/(4 + vel*2);
		isMoving = false;
	}

	if(vel > .01) {
		hop();
	}
	else
		vel = 0;

	
	float mouseDir = calcPtDir(320,240, i->getMouseX(), i->getMouseY());
	toolDirection(cDir-90 + -mouseDir);

	if(i->checkLeftMouse())
		attack();
}

void Player :: land(GraphicsOGL* gl) {
	Character :: land(gl);
}
