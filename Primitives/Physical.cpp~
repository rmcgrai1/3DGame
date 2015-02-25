// Physical.cpp


#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "Physical.h"
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"


Physical :: Physical(float myX, float myY, float myZ) : Instantiable() {
	x = myX;
	y = myY;
	z = myZ;
}

void Physical :: update(GraphicsOGL* gl, float deltaTime) {
	Instantiable :: update(gl, deltaTime);

	updateMotion(deltaTime);
}
	
void Physical :: draw(GraphicsOGL* gl, float deltaTime) {
	Instantiable :: draw(gl, deltaTime);
}

void Physical :: setZ(float newZ) {
	z = newZ;
}

bool Physical :: collideHeightmap(Heightmap* hm) {
	float h;
	h = hm->getHeightXY(x,y);

	if(h == -1)
		return false;
	else {
		z = h;
		return true;
	}
}

void Physical :: updateMotion(float deltaTime) {
	xP = x;
	yP = y;
	zP = z;
	
	x += deltaTime * calcLenX(vel, direction);
	y += deltaTime * calcLenY(vel, direction);
}
