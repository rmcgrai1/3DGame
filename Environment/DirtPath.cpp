// DirtPath.cpp
// Ryan McGrail

#include "DirtPath.h"
#include "../Graphics/GraphicsOGL.h"

// Constructor
DirtPath :: DirtPath() {
	numPts = 0;
}

// Add Point to List
void DirtPath :: addPt(float x,float y,float z) {

	// If Too Many Points, Quit
	if(numPts >= 100)
		return;

	// Add New Point
	pts[numPts*3+0] = x;
	pts[numPts*3+1] = y;
	pts[numPts*3+2] = z;

	// Increment # of Points
	numPts++;
}

// Drawing (Handled in Terrain Shader)
void DirtPath :: draw(GraphicsOGL* gl, float deltaTime) {
}

// Updating
void DirtPath :: update(GraphicsOGL* gl, float deltaTime) {
}
