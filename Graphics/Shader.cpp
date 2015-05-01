// Shader.cpp
// Ryan McGrail

#define GL_GLEXT_PROTOTYPES

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../IO/FileIO.h"
#include "Shader.h"

using namespace std;


// Constructor
Shader :: Shader(string myName) {

	// Create Shader Program
	program = glCreateProgram();

	// If Error, QUIT!
	if (program == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// Get Shader Directory
	string dir;
	name = myName;
	dir = "Resources/Shaders/" + name;
	string vs, fs;

	// Attempt to Read Vertex Shader File
	if (!FileIO::readFileIntoString(dir + "/vertex.sh", vs))
		exit(1);

	// Attempt to Read Fragment Shader File
	if (!FileIO::readFileIntoString(dir + "/frag.sh", fs))
		exit(1);

	// Add, Compile Vertex and Fragment Shader
	addSubShader(vs.c_str(), GL_VERTEX_SHADER);
	addSubShader(fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	// Link Shader Program
	glLinkProgram(program);
	
	// If Failed, Print Errors
	glGetProgramiv(program, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// Validate Shader
	glValidateProgram(program);
	
	// If Failed, Print Errors
	glGetProgramiv(program, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}
}

// Get Shader Program
GLuint Shader :: getProgram() {
	return program;
}

// Get Shader Name
string Shader :: getName() {
	return name;
}

// Add Subshader (Vertex or Fragment)
void Shader :: addSubShader(const char* pShaderText, GLenum ShaderType) {

	// Create Shader
	GLuint ShaderObj = glCreateShader(ShaderType);

	// If Error, Quit!!
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0]= strlen(pShaderText);
	
	// Load in Shader Source Code
	glShaderSource(ShaderObj, 1, p, Lengths);
	
	// Compile Code
	glCompileShader(ShaderObj);
	
	// If Failed, Print Error Text!!
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// Attach Shader to Program
	glAttachShader(program, ShaderObj);
}
