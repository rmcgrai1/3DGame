// Camera.cpp
// Ryan McGrail

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "../Functions/Math2D.h"
#include "GraphicsOGL.h"
#include "Camera.h"


// Constructor
Camera :: Camera() {

	// Initialize Variables
	camX = camY = camZ = toX = toY = toZ = newCamX = newCamY = newCamZ = camDir = 0;
	camZ = 270;
	toZ = 270;
	newCamZ = 270;
}

// Prepare Camera for Setting Projection
void Camera :: setProjectionPrep(float cX, float cY, float cZ, float tX, float tY, float tZ) {

	// Set New Camera Position
	newCamX = cX;
	newCamY = cY;
	newCamZ = cZ;
	
	// Set New Camera Focus Point
	toX = tX;
	toY = tY;
	toZ = tZ;
	
	// Update Camera Direction
	camDir = calcPtDir(newCamX, newCamY, toX, toY);
}

// Get Camera XY Direction		
float Camera :: getCamDir() {
	return camDir;
}

// Set Projection for 3D Camera
void Camera :: setProjection(GraphicsOGL* gl) {
	float cX = newCamX, cY = newCamY, cZ = newCamZ;
	float camSpeed = 5;

	// Calculate Some Delta Zs to Smoothly Move Camera and for Sound Positioning
	float cZD, toZD;
	cZD = (cZ - camZ)/(2*camSpeed);
	toZD = (toZ - focusZ)/(2*camSpeed);
	
	// Smoothly Move Camera along Up-Down Axis
	camZ += cZD;
	focusZ += toZD;
	
	//Update Listener Source
	float n, nX, nY, nZ;
	n = (float) (sqrt(sqr(toX-cX) + sqr(toY-cY) + sqr(focusZ-camZ)));
	nX = (toX-cX)/n;
	nY = (toY-cY)/n;
	nZ = (focusZ-camZ)/n;
	
	// Update Listener Position for Sounds
	gl->getSoundController()->updateListener(cX,cY,camZ, cX-camX,cY-camY,cZD, nX,nY,nZ, 0,0,1);
		
	
	// Change to projection matrix.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up Perspective
	float widthHeightRatio = (float) gl->getScreenWidth() / (float) gl->getScreenHeight();
	gluPerspective(45, widthHeightRatio, 1, 5000);
	gluLookAt(cX, cY, camZ, toX, toY, focusZ, 0, 0, 1);

	// Move Camera
	camX = cX;
	camY = cY;

	// Update Camera Direction
	camDir = calcPtDir(camX,camY,toX,toY);

	// Change back to model view matrix.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
}


// Get Camera XYZ Direction, Normalized
void Camera :: getNormal(float vec[3]) {

	// Create Vector of Direction from Camera to Focus Point
	vec[0] = toX-camX;
	vec[1] = toY-camY;
	vec[2] = toZ-camZ;

	// Normalize Vector
	float len = sqrt(sqr(vec[0]) + sqr(vec[1]) + sqr(vec[2]));
	vec[0] /= len;
	vec[1] /= len;
	vec[2] /= len;
}

// Get Camera X
float Camera :: getX() {
	return camX;
}

// Get Camera Y
float Camera :: getY() {
	return camY;
}

// Get Camera Z
float Camera :: getZ() {
	return camZ;
}

// Get Camera XYZ Position
void Camera :: getPosition(float vec[3]) {
	vec[0] = camX;
	vec[1] = camY;
	vec[2] = camZ;
}

// Get Camera XYZ Position for Shaders
void Camera :: getShaderPosition(float vec[3]) {
	vec[0] = -camY;
	vec[2] = -camX;
	vec[1] = camZ;
}

// Get Camera XYZ Direction for Shaders
void Camera :: getDirection(float vec[3]) {
	vec[0] = 0;
	vec[1] = -calcPtDir(0,camZ,calcPtDis(camX,camY,toX,toY),focusZ)/180.*3.14159;
	vec[2] = -calcPtDir(camX,camY,toX,toY)/180.*3.14159;
}
