// Physical.cpp


#include <iostream>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "Physical.h"
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;



// Set up Gravity Constant
const float Physical :: GRAVITY_ACCELERATION = -.15; //-.125;


// CONSTRUCTOR
Physical :: Physical(float myX, float myY, float myZ) : Instantiable() {

	// Initialize Player at Position
	xP = x = myX;
	yP = y = myY;
	floorZ = zP = z = myZ;

	// Initialize Velocity and Direction to 0
	vel = zVel = 0;
	direction = 0;

	onGround = true;
}

void Physical :: update(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: update(gl, deltaTime);

	// Update Physics
	updateMotion(deltaTime);
	// Update Collisions
	collideHeightmap(gl, gl->getHeightmap());
}
	
void Physical :: draw(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: draw(gl, deltaTime);	
}

void Physical :: destroy() {
	Instantiable :: destroy();
}

bool Physical :: checkOnScreen(GraphicsOGL* gl) {

	float camPos[3], camX, camY, camFOV, camDir;
	gl->getCamera()->getPosition(camPos);
	camX = camPos[0];
	camY = camPos[1];
	camDir = gl->getCamera()->getCamDir();

	camFOV = 45;

	float curX, curY, curZ, curRad;

	curX = x;
	curY = y;

	isOnScreen = (abs(calcAngleDiff(calcPtDir(camX,camY,curX,curY),camDir)) <= camFOV);

	if(isOnScreen)
		fidelity = 1- calcPtDis(curX,curY,camX,camY)/2000;

	return isOnScreen;
}


// ACCESSOR/MUTATOR FUNCTIONS
	void Physical :: setX(float newX) {
		x = newX;
	}
	void Physical :: setY(float newY) {
		y = newY;
	}
	void Physical :: setZ(float newZ) {
		z = newZ;
	}

	float Physical :: getX() {
		return x;
	}
	float Physical :: getY() {
		return y;
	}
	float Physical :: getZ() {
		return z;
	}
	float Physical :: getVelocity() {
		return vel;
	}
	float Physical :: getDirection() {
		return direction;
	}


bool Physical :: collideHeightmap(GraphicsOGL* gl, Heightmap* hm) {

	// Get Height from Heightmap at Position
	float h = hm->getHeightXY(x,y);

	// If Off Map, Ignore
	if(h == -1)
		return false;

	// Otherwise, Check Collisions!
	else {

		// Landing
		if(z < h+4 && zVel < 0) {

			// Move Object to Floor Height
			floorZ = z = h;

			// Run Landing Function (Might Bounce, Play Sound?)
			if(zVel != GRAVITY_ACCELERATION) {
				land(gl);
			}

			// If Z Vel Not Bouncing after Land(), Make Sure it's Set to 0!
			if(zVel < 0)
				zVel = 0;

			onGround = true;
		}

		return true;
	}
}

void Physical :: updateMotion(float deltaTime) {

	// Store Current Position as Previous
	xP = x;
	yP = y;
	zP = z;

	// Add Velocities to Position
	x += deltaTime * calcLenX(vel, direction);
	y += deltaTime * calcLenY(vel, direction);
	z += deltaTime * zVel;

	// Add Z Gravity to Z Velocity
	zVel += GRAVITY_ACCELERATION;

	onGround = false;
}
