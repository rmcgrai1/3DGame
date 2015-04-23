// DeathPuff.cpp
// Ryan McGrail

// (These are the puffs that appear when a character dies.)

#include "../Functions/Math2D.h"
#include <iostream>
#include <cmath>
#include "../Graphics/GraphicsOGL.h"
#include "DeathPuff.h"
#include "Particle.h"
using namespace std;


// Constructor
DeathPuff :: DeathPuff(float nX,float nY,float nZ, float nTX, float nTY, float nTZ, float startR, float div) : Particle(nX,nY,nZ) {
	
	// Get Direction Normal
	toX = nTX;
	toY = nTY;
	toZ = nTZ;

	// Normalize Direction
	float n = sqrt(toX*toX + toY*toY + toZ*toZ);
	toX /= n;
	toY /= n;
	toZ /= n;

	// Set Starting Radius
	puffSize = startR;

	// Initialize Starting Percentage, and Speed of Travel
	toPerc = 0;
	percDiv = div;
}

// Update Function
void DeathPuff :: update(GraphicsOGL* gl, float deltaTime) {

	// Move Puff
	toPerc += (1 - toPerc)/percDiv;

	// If Done Moving, Destroy Puff
	if(1-toPerc < .01)
		destroy();
}

// Draw Function		
void DeathPuff :: draw(GraphicsOGL* gl, float deltaTime) {

	// Distance of Travel
	float flyRad = 40;
	// Percentage that Starts at 0, Reaches Max Halfway, and then Returns to 0
	float movePerc = abs(sin(toPerc*3.14159));
	
	// Calculate Point along Line
	float dX, dY, dZ;
	dX = x + flyRad*toPerc*toX;
	dY = y + flyRad*toPerc*toY;
	dZ = z + flyRad*toPerc*toZ;

	
	// Shake Puff as Moving Out
	float s = 2;
	float aX, aY, aZ;
	aX = toPerc*s*(-.5+rnd());
	aY = toPerc*s*(-.5+rnd());
	aZ = toPerc*s*(-.5+rnd());

	
	// Clear Transformations
	gl->transformClear();
		// Translate to Position
		gl->transformTranslation(dX+aX,dY+aY,dZ+aZ);
		// Draw 3D Sphere at Position
		gl->draw3DSphere(0,0,0,movePerc*puffSize,4);
	// Clear Transformations
	gl->transformClear();
}
