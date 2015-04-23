// Physical.cpp
// Ryan McGrail

#include <iostream>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "Physical.h"
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
#include "../Environment/Shapes/Piece.h"
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
	onHeightmap = true;
}

// Update Function
void Physical :: update(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: update(gl, deltaTime);

	// Update Physics
	updateMotion(deltaTime);
	// Update Collisions
	bool onHM, onP = false;	
	onHM = collideHeightmap(gl, gl->getHeightmap());

	if(this == gl->getPlayer())
		onP = collidePieces();

	if(onHM)
		onHeightmap = true;
	else if(onP)
		onHeightmap = false;
}
	
// Draw Function
void Physical :: draw(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: draw(gl, deltaTime);	
}

// Destroy Function
void Physical :: destroy() {
	Instantiable :: destroy();
}

// Function for Checking if Onscreen
bool Physical :: checkOnScreen(GraphicsOGL* gl) {

	// Get Camera Variables
	float camPos[3], camX, camY, camFOV, camDir;
	gl->getCamera()->getPosition(camPos);
	camX = camPos[0];
	camY = camPos[1];
	camDir = gl->getCamera()->getCamDir();
	camFOV = 45;

	float curX, curY;
	curX = x;
	curY = y;

	// If Direction from Camera to Player is Within its Field of View (FOV), Assume Player is Onscreen
	isOnScreen = (abs(calcAngleDiff(calcPtDir(camX,camY,curX,curY),camDir)) <= camFOV);

	// If Onscreen, Set Fidelity
	if(isOnScreen)
		fidelity = 1- calcPtDis(curX,curY,camX,camY)/2000;

	return isOnScreen;
}


// ACCESSOR/MUTATOR FUNCTIONS
	void Physical :: setX(float newX) {
		//xP = x;
		x = newX;
	}
	void Physical :: setY(float newY) {
		//yP = y;
		y = newY;
	}
	void Physical :: setZ(float newZ) {
		//zP = z;
		z = newZ;
	}
	void Physical :: setZVelocity(float newZVel) {
		zVel = newZVel;
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
	float Physical :: getXPrev() {
		return xP;
	}
	float Physical :: getYPrev() {
		return yP;
	}
	float Physical :: getZPrev() {
		return zP;
	}
	float Physical :: getVelocity() {
		return vel;
	}
	float Physical :: getDirection() {
		return direction;
	}
	float Physical :: getZVelocity() {
		return zVel;
	}


// Placing on Ground (Assume the Player is on the Ground!!)
void Physical :: placeOnGround() {

	if(zVel <= 0) {
		floorZ = z;

		// Run Landing Function (Might Bounce, Play Sound?)
		if(zVel < 2*GRAVITY_ACCELERATION)
			land();

		// If Z Vel Not Bouncing after Land(), Make Sure it's Set to 0!
		if(zVel < 0)
			zVel = 0;

		onGround = true;
	}
}

// Colliding with Pieces
bool Physical :: collidePieces() {

	bool didCollide = false;

	// Loop Through Each Piece, Run Collision Script
	for(int i = 0; i < Piece::pieceList.size(); i++)
		didCollide = (didCollide || Piece::pieceList[i]->collide(this));

	return didCollide;
}

// Colliding w/ Heightmap
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
			z = h;
			
			// Assume Player is On Ground
			placeOnGround();

			return true;
		}
		else
			return false;
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
