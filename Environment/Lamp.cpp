// Lamp.cpp


#include "../Graphics/Texture.h"
#include "../Functions/Math2D.h"
#include <iostream>
#include <vector>
#include "Lamp.h"
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
using namespace std;

vector<Lamp*> Lamp :: lampList;

#define LIGHT_TIMER_MAX 5

Lamp :: Lamp(float nX, float nY) : Environmental(nX,nY) {
	height = 0;
	rotate = 0;

	xydir = rnd()*360;

	R = 1;
	G = 1;
	B = 1;
	A = 1;

	lampList.push_back(this);

	lightTimer = -1;
}

Lamp :: Lamp(float nX, float nY, float nR, float nG, float nB, float nA) : Environmental(nX,nY) {
	height = 0;
	rotate = 0;

	xydir = rnd()*360;

	R = nR;
	G = nG;
	B = nB;
	A = nA;

	lampList.push_back(this);

	lightTimer = -1;
}


Lamp :: Lamp(float nX, float nY, float nZ) : Environmental(nX,nY,nZ) {
	height = 0;
	rotate = 0;

	xydir = rnd()*360;

	R = 1;
	G = 1;
	B = 1;
	A = 1;

	lampList.push_back(this);
}

float Lamp :: getLightX() {
	return lightX;
}
float Lamp :: getLightY() {
	return lightY;
}
float Lamp :: getLightZ() {
	return lightZ;
}
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

float Lamp :: getLightRadius() {
	return rad + 5*(rnd()-.5);
}

void Lamp :: damage(float dmg) {
}

void Lamp :: update(GraphicsOGL* gl, float deltaTime) {
	Environmental::update(gl,deltaTime);

	rotate += 3*deltaTime;
	
	lightTimer -= deltaTime;
	if(lightTimer <= -1) {
		rad = 150 + 50*rnd();
		lightTimer = LIGHT_TIMER_MAX*rnd();
	}
}
void Lamp :: draw(GraphicsOGL* gl, float deltaTime) {

	float w = 15;
	float h = 40;
	float lantR = 4;
	float lantH = 6;

	Texture* texWood = gl->getTextureController()->getTexture("bark");

	gl->transformClear();
		gl->transformTranslation(x,y,z-5);
		gl->transformRotationZ(xydir);
		gl->transformTranslation(0,-w*.8,h*.75);
		gl->transformTranslation(0,0,lantH);
		gl->transformRotationY(sin(rotate/180*3.14159)*20);
		gl->transformTranslation(0,0,-lantH);
			gl->draw3DFrustem(0,0,0,lantR-1,lantR+1,lantH,3);

			lightX = x + calcLenX(-w*.8,xydir);
			lightY = y + calcLenY(-w*.8,xydir);
			lightZ = z + h*.75;

	gl->transformClear();
		gl->transformTranslation(x,y,z-5);
		gl->transformRotationZ(xydir);
			gl->draw3DBlock(-2,-w,h+2,2,w*.125,h-2,texWood);
			gl->draw3DFrustem(0,0,0,2.3,2,h*1.1,3,texWood);
	gl->transformClear();
}

