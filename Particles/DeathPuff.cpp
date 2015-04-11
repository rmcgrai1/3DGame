// DeathPuff.cpp


#include <iostream>
#include "../Graphics/GraphicsOGL.h"
#include "DeathPuff.h"
#include "Particle.h"
using namespace std;

DeathPuff :: DeathPuff(float nX,float nY,float nZ, float nTX, float nTY, float nTZ, float startR, float div) : Particle(nX,nY,nZ) {
	toX = nTX;
	toY = nTY;
	toZ = nTZ;

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

	float dX, dY, dZ;
	dX = (1-toPerc)*x + toPerc*toX;
	dY = (1-toPerc)*y + toPerc*toY;
	dZ = (1-toPerc)*z + toPerc*toZ;

	gl->transformClear();
		gl->transformTranslation(dX,dY,dZ);
		gl->draw3DSphere(0,0,0,toPerc*rad,10);
	gl->transformClear();
}
