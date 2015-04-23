// Particle.cpp
// Ryan McGrail


#include "../Graphics/GraphicsOGL.h"
#include "Particle.h"
#include "../Primitives/Instantiable.h"

// Constructor
Particle :: Particle(float nX, float nY, float nZ) : Instantiable() {

	// Set Position
	x = nX;
	y = nY;
	z = nZ;
}

// Update Particle
void Particle :: update(GraphicsOGL* gl, float deltaTime) {
	Instantiable :: update(gl, deltaTime);
}

// Draw Particle
void Particle :: draw(GraphicsOGL* gl, float deltaTime) {
	Instantiable :: draw(gl, deltaTime);
}
