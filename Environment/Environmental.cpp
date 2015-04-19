// Environmental.cpp

#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Functions/Math2D.h"
#include "../Primitives/Instantiable.h"

Environmental :: Environmental(float nX, float nY) {
	health = 100;
	x = nX;
	y = nY;
	z = -1;
	onGround = false;
}

Environmental :: Environmental(float nX, float nY, float nZ) {
	health = 100;
	x = nX;
	y = nY;
	z = nZ;
	onGround = false;
}

void Environmental :: update(GraphicsOGL* gl, float deltaT) {
	placeOnGround(gl);
}

void Environmental :: draw(GraphicsOGL* gl, float deltaT) {
}

bool Environmental :: checkOnScreen(GraphicsOGL* gl) {

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
		fidelity = 1;// - calcPtDis(curX,curY,camX,camY)/2000;

	return isOnScreen;
}

float Environmental :: getX() {
	return x;
}

float Environmental :: getY() {
	return y;
}

float Environmental :: getZ() {
	return z;
}

void Environmental :: placeOnGround(GraphicsOGL* gl) {
	if(z == -1 && !onGround) {
		onGround = true;
		z = gl->getHeightmap()->getHeightXY(x,y);
	}
}
