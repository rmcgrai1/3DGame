// DeathPuff.cpp


#include "../Functions/Math2D.h"
#include <iostream>
#include <cmath>
#include "../Graphics/GraphicsOGL.h"
#include "DeathPuff.h"
#include "Particle.h"
using namespace std;

DeathPuff :: DeathPuff(float nX,float nY,float nZ, float nTX, float nTY, float nTZ, float startR, float div) : Particle(nX,nY,nZ) {
	toX = nTX;
	toY = nTY;
	toZ = nTZ;

	float n = sqrt(toX*toX + toY*toY + toZ*toZ);
	toX /= n;
	toY /= n;
	toZ /= n;

	rad = startR;

	toPerc = 0;
	percDiv = div;
}

void DeathPuff :: update(GraphicsOGL* gl, float deltaTime) {

	toPerc += (1 - toPerc)/percDiv;

	if(1-toPerc < .01)
		destroy();
}
		
void DeathPuff :: draw(GraphicsOGL* gl, float deltaTime) {

	float flyRad = 40;
	float movePerc = abs(sin(toPerc*3.14159));
	float dX, dY, dZ;
	dX = x + flyRad*toPerc*toX;
	dY = y + flyRad*toPerc*toY;
	dZ = z + flyRad*toPerc*toZ;

	float s = 2;
	float aX, aY, aZ;
	aX = toPerc*s*(-.5+rnd());
	aY = toPerc*s*(-.5+rnd());
	aZ = toPerc*s*(-.5+rnd());

	//if(!gl->isPCSlow())
	//	gl->enableShader("Character");	
	gl->transformClear();
		gl->transformTranslation(dX+aX,dY+aY,dZ+aZ);
		gl->draw3DSphere(0,0,0,movePerc*rad,4);
	gl->transformClear();

	gl->disableShaders();
}
