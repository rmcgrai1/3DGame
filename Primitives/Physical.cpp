// Physical.cpp


#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "Physical.h"
#include "../Functions/Math2D.h"


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

void Physical :: updateMotion(float deltaTime) {
	xP = x;
	yP = y;
	zP = z;
	
	x += deltaTime * calcLenX(vel, direction);
	y += deltaTime * calcLenY(vel, direction);
}
