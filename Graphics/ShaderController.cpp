// ShaderController.cpp

#include <string>
#include <map>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Shader.h"
#include "ShaderController.h"
using namespace std;

ShaderController :: ShaderController() {
	initialize();
}


Shader* ShaderController :: getShader(string name) {
	return shaderMap[name];
}
GLuint ShaderController :: getProgram(string name) {
	return getShader(name)->getProgram();
}

void ShaderController :: initialize() {
	addShader("Diffuse");
	//addShader("Invert");
	addShader("Galaxy");
}
void ShaderController :: addShader(string name) {
	shaderMap[name] = new Shader(name);
}
