// Shader.h
// Ryan McGrail

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
using namespace std;

class Shader {
	public:
		Shader(string);								// Constructor
		GLuint getProgram();						// Get Shader Program
		string getName();							// Get Shader Name

	private: 
		void addSubShader(const char*, GLenum);		// Add Subshader (Vertex or Fragment)
		GLuint program;								// Shader Program
		string name;								// Shader Name
};

#endif
