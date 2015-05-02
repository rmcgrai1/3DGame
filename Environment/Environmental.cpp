// Environmental.cpp
// Ryan McGrail

#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Functions/Math2D.h"
#include "../Primitives/Instantiable.h"

// Constructor, XY
Environmental :: Environmental(float nX, float nY) {
	health = 100;
	x = nX;
	y = nY;
	z = -1;
	onGround = false;
}

// Constructor, XYZ
Environmental :: Environmental(float nX, float nY, float nZ) {
	health = 100;
	x = nX;
	y = nY;
	z = nZ;
	onGround = false;
}

// Updating
void Environmental :: update(GraphicsOGL* gl, float deltaT) {
	placeOnGround(gl);
}

// Drawing
void Environmental :: draw(GraphicsOGL* gl, float deltaT) {
}

// Checking if Object is On Screen
bool Environmental :: checkOnScreen(GraphicsOGL* gl) {

	// Get Camera Vars
	float camPos[3], camX, camY, camFOV, camDir;
	gl->getCamera()->getPosition(camPos);
	camX = camPos[0];
	camY = camPos[1];
	camDir = gl->getCamera()->getCamDir();
	camFOV = 45;

	// Get Position Vars
	float curX, curY, curRad;
	curX = x;
	curY = y;

	// If Within Camera FOV, On Screen
	isOnScreen = (abs(calcAngleDiff(calcPtDir(camX,camY,curX,curY),camDir)) <= camFOV);
	if(isOnScreen)
		fidelity = 1;// - calcPtDis(curX,curY,camX,camY)/2000;

	return isOnScreen;
}

// Get X
float Environmental :: getX() {
	return x;
}
// Get Y
float Environmental :: getY() {
	return y;
}
// Get Z
float Environmental :: getZ() {
	return z;
}

// Place Object on Heightmap
void Environmental :: placeOnGround(GraphicsOGL* gl) {

	// If Not Placed, Place!
	if(z == -1 && !onGround) {
		onGround = true;
		z = gl->getHeightmap()->getHeightXY(x,y);
	}
}
