// DirtPath.cpp

#include "DirtPath.h"
#include "../Graphics/GraphicsOGL.h"

DirtPath :: DirtPath() {
	numPts = 0;
}

void DirtPath :: addPt(float x,float y,float z) {
	if(numPts >= 100)
		return;

	pts[numPts*3+0] = x;
	pts[numPts*3+1] = y;
	pts[numPts*3+2] = z;

	numPts++;
}

void DirtPath :: draw(GraphicsOGL* gl, float deltaTime) {
}

void DirtPath :: update(GraphicsOGL* gl, float deltaTime) {
}
