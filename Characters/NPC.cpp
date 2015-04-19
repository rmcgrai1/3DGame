// NPC.cpp


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
#include "Character.h"
#include "NPC.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;

#define MODE_CHASE 1
#define MODE_ATTACK 2
#define MODE_ROAM 0


//float nCDir = 0;
//float jumpSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*24));

NPC :: NPC(float x, float y, float z) : Character(x,y,z) {
}	

void NPC :: update(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("NPC.cpp, update()");

	//Inputcontroller will be simulated
	Character :: update(gl, deltaTime);

	updateControl(gl,deltaTime);
}

void NPC :: draw(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("NPC.cpp, draw()");

	Character :: draw(gl, deltaTime);
}

void NPC :: updateControl(GraphicsOGL* gl, float deltaTime) {
	InputController* i = gl->getInputController();

	int mode;

	Character* p = gl->getPlayer();
	float toPlayerDir;
	toPlayerDir = calcPtDir(x,y,p->getX(),p->getY());

	if(calcPtDis(x,y,p->getX(),p->getY()) > 150 || abs(calcAngleDiff(toPlayerDir,faceDir)) > 50)
		mode = MODE_ROAM;
	else if(calcPtDis(x,y,p->getX(),p->getY()) > p->getSize()+size+3)
		mode = MODE_CHASE;
	else
		mode = MODE_CHASE;
	//else
	//	mode = MODE_ATTACK;

	if(mode == MODE_ROAM) {
		float dir = 5*rnd(-1,1);
		isMoving = true;

		direction += dir;

		faceDirection(direction);
		toolDirection(direction);

		vel = 1;
	}
	else if(mode == MODE_CHASE) {
		float dir = toPlayerDir;
		direction += calcTurnToDir(direction, dir);

		isMoving = true;
		faceDirection(direction);
		toolDirection(direction);

		vel = 2;
	}
	else if(mode == MODE_ATTACK) {
		float dir = calcPtDir(x,y,p->getX(),p->getY());

		toolDirection(direction);
		attack();
	}

	hop();
}



void NPC :: land() {
}
