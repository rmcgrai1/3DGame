// Lamp.cpp
// Ryan McGrail

#include "../Graphics/Texture.h"
#include "../Functions/Math2D.h"
#include "../Graphics/TextureController.h"
#include <iostream>
#include <vector>
#include "Lamp.h"
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
using namespace std;

vector<Lamp*> Lamp :: lampList;

#define LIGHT_TIMER_MAX 5

// Constructor, Position
Lamp :: Lamp(float nX, float nY) : Environmental(nX,nY) {
	rotate = 0;

	// Randomize Direction
	xydir = rnd()*360;

	// Color = White
	R = 1;
	G = 1;
	B = 1;
	A = 1;

	lampList.push_back(this);

	lightTimer = -1;
}

// Constructor, Position & Color
Lamp :: Lamp(float nX, float nY, float nR, float nG, float nB, float nA) : Environmental(nX,nY) {
	rotate = 0;

	// Randomize Direction
	xydir = rnd()*360;

	// Set Color
	R = nR;
	G = nG;
	B = nB;
	A = nA;

	lampList.push_back(this);

	lightTimer = -1;
}

// Constructor, Position & Z
Lamp :: Lamp(float nX, float nY, float nZ) : Environmental(nX,nY,nZ) {
	rotate = 0;

	// Randomize Direction
	xydir = rnd()*360;

	// Color = White
	R = 1;
	G = 1;
	B = 1;
	A = 1;

	lampList.push_back(this);
	lightTimer = -1;
}

// Getting Light Position
float Lamp :: getLightX() {
	return lightX;
}
float Lamp :: getLightY() {
	return lightY;
}
float Lamp :: getLightZ() {
	return lightZ;
}

// Getting Light Color
float Lamp :: getLightR() {
	return R;
}
float Lamp :: getLightG() {
	return G;
}
float Lamp :: getLightB() {
	return B;
}
float Lamp :: getLightA() {
	return A;
}

// Getting Light Radius
float Lamp :: getLightRadius() {
	return rad + 5*(rnd()-.5);
}

// Damaging Lamp
void Lamp :: damage(float dmg) {
}

// Updating
void Lamp :: update(GraphicsOGL* gl, float deltaTime) {
	Environmental::update(gl,deltaTime);
	
	// Rotate Lantern
	rotate += 3*deltaTime;
	
	// Update Light Radius Flickering
	lightTimer -= deltaTime;
	if(lightTimer <= -1) {
		rad = 150 + 50*rnd();
		lightTimer = LIGHT_TIMER_MAX*rnd();
	}
}

// Drawing
void Lamp :: draw(GraphicsOGL* gl, float deltaTime) {

	float w = 15;
	float h = 40;
	float lantR = 4;
	float lantH = 6;

	// Enable Bark Shader
	gl->enableShader("pineBark");

	// Get Texture
	Texture* texWood = TextureController::getTexture("bark");
	
	// Drawing Lantern
	gl->transformClear();
		gl->transformTranslation(x,y,z-5);
		gl->transformRotationZ(xydir);
		gl->transformTranslation(0,-w*.8,h*.75);
		gl->transformTranslation(0,0,lantH);
		gl->transformRotationY(sin(rotate/180*3.14159)*20);
		gl->transformTranslation(0,0,-lantH);
			gl->draw3DFrustem(0,0,lantH-1,lantR+1,lantR-1,1,3);
			gl->draw3DFrustem(0,0,-1,lantR-2,lantR-1,lantH-1,3);

			lightX = x + calcLenX(-w*.8,xydir);
			lightY = y + calcLenY(-w*.8,xydir);
			lightZ = z + h*.75;

	// Drawing Wood Frame
	gl->transformClear();
		gl->transformTranslation(x,y,z-5);
		gl->transformRotationZ(xydir);
			gl->draw3DBlock(-2,-w,h+2,2,w*.125,h-2,texWood);
			gl->draw3DFrustem(0,0,0,2.3,2,h*1.1,3,texWood);
	gl->transformClear();

	gl->disableShaders();
}

