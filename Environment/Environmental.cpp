// Environmental.cpp

#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Instantiable.h"

Environmental :: Environmental(float nX, float nY) {
	health = 100;
	x = nX;
	y = nY;
}

void Environmental :: update(GraphicsOGL* gl, float deltaT) {
	placeOnGround(gl);
}

void Environmental :: draw(GraphicsOGL* gl, float deltaT) {
}

float Environmental :: getX() {
	return x;
}

float Environmental :: getY() {
	return y;
}

float Environmental :: getZ() {
	return z;
}

void Environmental :: placeOnGround(GraphicsOGL* gl) {
	if(!onGround) {
		onGround = true;
		z = gl->getHeightmap()->getHeightXY(x,y);
	}
}
