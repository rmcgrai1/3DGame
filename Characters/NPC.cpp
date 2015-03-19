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


float nCDir = 0;
float jumpSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*24));

NPC :: NPC(float x, float y, float z) : Character(x,y,z) {
}

void NPC :: update(GraphicsOGL* gl, float deltaTime) {
	//Inputcontroller will be simulated
	Character :: update(gl, deltaTime);

	updateMovement(gl,deltaTime);
}

void NPC :: draw(GraphicsOGL* gl, float deltaTime) {

	Character :: draw(gl, deltaTime);
}

void Player :: updateControl(GraphicsOGL* gl, float deltaTime) {
	srand(time(NULL));
	InputController* i = gl->getInputController();
	float dir = 0, cDir = gl->getCamDir(), aDir;
	aDir = dir-90;
	int randMove = rand()%10;
	switch(randMove){
		case 1: 
			dir = 90;
			aDir = dir - 90;
			break; 
		case 2: 
			dir = -90;
			aDir = dir - 90;
			break;
		case 3: 
			dir = 0;
			aDir = dir - 90;
			break;
		case 4: 
			dir = 180;
			aDir = dir - 90;
			break;
		case 5: 
			dir = 45;
			aDir = dir - 90;
			break;
		case 6: 
			dir = 135;
			aDir = dir - 90;
			break;
		default:
			dir = i -> getWASDDir();
			aDir = dir - 90;
			break;
	}

	/*/ If Jump Button Pressed...
	if(i->checkLetter('u')) {
		if(onGround) {
			zVel = jumpSpeed;
			onGround = false;
		}
	}
	else if(!onGround && zVel > 0) {
		zVel += (0 - zVel)/3;
	}*/

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



void NPC :: land() {
}
