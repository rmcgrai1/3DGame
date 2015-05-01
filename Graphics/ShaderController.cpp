// ShaderController.cpp
// Ryan McGrail

#include <string>
#include <map>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Shader.h"
#include "ShaderController.h"
using namespace std;

// Constructor
ShaderController :: ShaderController() {
	initialize();
}

// Get Shader w/ Name
Shader* ShaderController :: getShader(string name) {
	return shaderMap[name];
}

// Get Shader Program w/ Name
GLuint ShaderController :: getProgram(string name) {
	return getShader(name)->getProgram();
}

// Initialize Shaders
void ShaderController :: initialize() {
	addShader("Diffuse");
	addShader("Invert");
	addShader("Blade");
	addShader("Grayscale");
	addShader("Galaxy");
	addShader("RainbowTexture");
	addShader("GalaxyTexture");
	addShader("Rimlighting");
	addShader("Water");
	addShader("Sky");
	addShader("Terrain");
	addShader("SmokeRing");
	addShader("Untextured");
	addShader("Character");
	addShader("pineBranch");
	addShader("pineBark");
	addShader("Piece");
}

// Load/Add New Shader
void ShaderController :: addShader(string name) {
	shaderMap[name] = new Shader(name);
}
