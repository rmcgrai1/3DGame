// Water.cpp
// Ryan McGrail

#include <iostream>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
using namespace std;


// Constructor
Water :: Water(float w, float h, float newSeaLevel) : Drawable2() {
	width = w;
	height = h;
	seaLevel = newSeaLevel;
}

// Get Sea Level (Z)
float Water :: getSeaLevel() {
	return seaLevel;
}

// Updating
void Water :: update(GraphicsOGL* gl, float deltaTime) {
}

// Drawing
void Water :: draw(GraphicsOGL* gl, float deltaTime) {

	// If PC Not too Slow, Enable Water Shader
	if(!gl->isPCSlow())
		gl->enableShader("Water");
		
	// Draw Water
	gl->draw3DFloor(0,0,width,height,seaLevel,NULL);

	// Disable Shader
	gl->disableShaders();
}
