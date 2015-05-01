// ShaderController.h
// Ryan McGrail

#ifndef SHADERCONTROLLER_H
#define SHADERCONTROLLER_H

#include <string>
#include <map>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Shader.h"

using namespace std;

class ShaderController {
	public:
		ShaderController();						// Constructor
		Shader* getShader(string);				// Getting Shader w/ Name
		GLuint getProgram(string);				// Getting Shader Program w/ Name

	private:
		void initialize();						// Initializing Shaders
		void addShader(string);					// Adding Shader
		map<string, Shader*> shaderMap;			// Map of Shaders
};

#endif
