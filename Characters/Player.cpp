// Player.cpp
// Ryan McGrail

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


float jumpSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*24));

// Constructor
Player :: Player(float x, float y, float z) : Character(x,y,z) {
	camDis = 70;
	camDir = 0;
}

void Player :: update(GraphicsOGL* gl, float deltaTime) {

	Character :: update(gl, deltaTime);

	// Update User Control of Player (If NOT Knocked Back)
	if(knockbackTimer == -1)
		updateControl(gl,deltaTime);	

	// Place Camera on Heightmap
	Heightmap* h = gl->getHeightmap();
	float cX, cY, cZ, dir = camDir;

	// Get Camera Position
	cX = x-calcLenX(camDis,camDir);
	cY = y-calcLenY(camDis,camDir);

	// If on Heightmap, Camera Z is Heightmap Z
	if(onHeightmap)
		cZ = h->getHeightXY(cX,cY);
	// Otherwise, Use Player's Floor Z
	else
		cZ = floorZ;

	// Set Camera Position Behind Player 
	gl->setProjectionPrep(cX,cY,cZ+8+10,x,y,floorZ+8);
}

// Draw Player
void Player :: draw(GraphicsOGL* gl, float deltaTime) {

	Character :: draw(gl, deltaTime);
}

void Player :: updateControl(GraphicsOGL* gl, float deltaTime) {

	InputController* i = gl->getInputController();
	float dir = i->getWASDDir(), cDir = gl->getCamDir(), d;

	// If Jump Button Pressed...
	if(i->checkKey(' ')) {
		// If on Ground, Jump
		if(onGround) {
			zVel = jumpSpeed;
			onGround = false;
		}
	}
	// Otherwise, if In Air, Limit Jumping Height
	else if(!onGround && zVel > 0)
		zVel += (0 - zVel)/3;

	// If a Moving Button is Held...
	if(dir != -1) {
	
		// Move Player, Increase Speed
		isMoving = true;
		vel += ((1 + i->getShift()*2) - vel)/(3 + (vel > 1)*10);

		// Rotate Camera Angle Based on Held Direction
		if(dir == 90 || dir == -90) {
			camDir = cDir;
			d = cDir - 90 + dir;	
		}
		else if(dir == 0 || dir == 180) {
			d = cDir - 90 + dir;	
			camDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else if(dir == 45 || dir == 135) {
			d = cDir - 90 + dir;	
			camDir = cDir + .2*calcTurnToDir(cDir,cDir-90+dir);
		}
		else {
			d = cDir - 90 + dir;	
			camDir = cDir - .2*calcTurnToDir(cDir,180+cDir-90+dir);
		}

		// Face Held Direction
		direction = d;
		faceDirection(d);
	}
	// Otherwise, Slow to Stop
	else {
		vel += (0 - vel)/(4 + vel*2);
		isMoving = false;
	}

	// If Moving, Hop
	if(vel > .01)
		hop();
	else
		vel = 0;

	// Get Direction from Center of Screen to Mouse
	float mouseDir = calcPtDir(320,240, i->getMouseX(), i->getMouseY());
	
	// Set Direction of Sword
	toolDirection(cDir-90 + -mouseDir);

	// If Left Mouse Clicked, Attack
	if(i->checkLeftMouse())
		attack();
}
