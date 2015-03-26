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
#include "Character.h"
#include "Player.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;


float nCDir = 0;
float jumpSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*24));


Player :: Player(float x, float y, float z) : Character(x,y,z) {
	
	camDis = 70;
}

void Player :: update(GraphicsOGL* gl, float deltaTime) {

	Character :: update(gl, deltaTime);

	// Update User Control of Player
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

		gl->setProjectionPrep(cX,cY,h->getHeightXY(cX,cY)+8+10,x,y,floorZ+8);
}

void Player :: draw(GraphicsOGL* gl, float deltaTime) {

	Character :: draw(gl, deltaTime);
}

void Player :: updateControl(GraphicsOGL* gl, float deltaTime) {
	InputController* i = gl->getInputController();
	float dir = i->getWASDDir(), cDir = gl->getCamDir(), aDir, d;
	aDir = dir-90;

	// If Jump Button Pressed...
	if(i->checkLetter('u')) {
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
		vel = 1 + i->getShift()*2;

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

		
		hop();

		direction = d;
		faceDirection(d);
	}
	else
		vel = 0;
}

void Player :: land() {
	Character :: land();
}
