// Texture.h
// Ryan McGrail

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Image.h"
using namespace std;

class Texture {
	public:
		Texture(string);							// Constructor: FileName
		Texture(string, bool);						// Constructor: FileName, isFont?
		Texture(string, const string&);				// Constructor: Name, FileName
		Texture(string, const string&, bool);		// Constructor: Name, FileName, isFont?

		string getName();							// Get Name of Texture
		int getWidth();								// Get Width of Texture
		int getHeight();							// Get Height of Texture

		void bind();								// Bind Texture
		void bind(GLenum);							// Bind Texture to Specific TextureUnit

		void unbind();								// Unbind Texture
		void unbind(GLenum);						// Unbind Texture from Specific TextureUnit
		
	private:
		load(string, bool);							// Load Texture

		string name;								// Name of Texture
		string fileName;							// Name of File

		GLuint m_textureObj;						// OpenGL index of Font
		Image* image;								// Image Object
};

#endif
