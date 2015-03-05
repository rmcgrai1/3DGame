// Physical.cpp


#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "Physical.h"
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"



// Set up Gravity Constant
const float Physical :: GRAVITY_ACCELERATION = -.5;


// CONSTRUCTOR
Physical :: Physical(float myX, float myY, float myZ) : Instantiable() {

	// Initialize Player at Position
	xP = x = myX;
	yP = y = myY;
	zP = z = myZ;

	// Initialize Velocity and Direction to 0
	vel = zVel = 0;
	direction = 0;
}

void Physical :: update(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: update(gl, deltaTime);

	// Update Physics
	updateMotion(deltaTime);
	// Update Collisions
	collideHeightmap(gl->getHeightmap());
}
	
void Physical :: draw(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Function
	Instantiable :: draw(gl, deltaTime);
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


bool Physical :: collideHeightmap(Heightmap* hm) {

	// Get Height from Heightmap at Position
	float h = hm->getHeightXY(x,y);

	// If Off Map, Ignore
	if(h == -1)
		return false;

	// Otherwise, Check Collisions!
	else {

		// Landing
		if(z < h && zVel < 0) {

			// Run Landing Function (Might Bounce, Play Sound?)
			land();

			// If Z Vel Not Bouncing, Make Sure it's Set to 0!
			if(zVel < 0)
				zVel = 0;

			// Move Object to Floor Height
			z = h;
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
}
