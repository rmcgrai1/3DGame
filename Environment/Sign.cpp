// Sign.cpp

#include "../Functions/Math2D.h"
#include "Sign.h"
#include "../GraphicsOGL.h"
#include <string>

Sign :: Sign(float nX, float nY, float nZ, string newText) : Environmental(nX, nY, nZ) {
	xyDir = rnd(360);
	text = newText;
	isDisplaying = false;
}

void Sign :: update(GraphicsOGL* gl, float deltaT) {
}
	
void Sign :: draw(GraphicsOGL* gl, float deltaT) {
	float w = 1;
	float h = 5;

	gl->draw3DBlock(-w,-w,w,h,w,0);
}
