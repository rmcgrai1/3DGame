// Water.cpp


#include <iostream>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
using namespace std;


Water :: Water(float w, float h, float newSeaLevel) : Drawable2() {
	width = w;
	height = h;
	seaLevel = newSeaLevel;
}

float Water :: getSeaLevel() {
	return seaLevel;
}

void Water :: update(GraphicsOGL* gl, float deltaTime) {
}

void Water :: draw(GraphicsOGL* gl, float deltaTime) {

	gl->enableShader("Water");
		gl->draw3DFloor(0,0,width,height,seaLevel,NULL);	
	gl->disableShaders();
}
