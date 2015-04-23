// Texture.cpp
// Ryan McGrail

#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "Image.h"
using namespace std;

// Constructors
Texture::Texture(string fileName) {

	name = fileName.c_str();

	load(fileName, false);
}

Texture::Texture(string fileName, bool isFont) {

	name = fileName.c_str();
	load(fileName, isFont);
}

Texture::Texture(string myName, const string& fileName) {

	name = myName.c_str();
	load(fileName, false);
}

Texture::Texture(string myName, const string& fileName, bool isFont) {

	name = myName.c_str();
	load(fileName, isFont);
}

// Load Texture
void Texture :: load(const string& fileName, bool isFont) {

	// Load Image
	image = new Image(fileName);

	// Generate Texture in OpenGL
	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	// If Font, DO NOT REPEAT TEXTURE and Use Nearest-Neighbor Filtering
	if(isFont) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	// Otherwise, Repeat Texture and Use Linear Filtering
	else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
		// REQUIRED FOR CIMG FORMATTING
		glPixelStoref(GL_PACK_ROW_LENGTH,1);
		glPixelStoref(GL_PACK_SKIP_PIXELS,1);
		glPixelStoref(GL_PACK_SKIP_ROWS,1);
		glPixelStoref(GL_PACK_ALIGNMENT,1);

	// Get Interleaved Data from Image
	unsigned char* data = new unsigned char[getWidth()*getHeight()*4];
	image->interleave(data);

	// Attach to OpenGL Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Get Name of Texture
string Texture :: getName() {
	return name;
}

// Get Width of Texture
int Texture :: getWidth() {
	return image->getWidth();
}
// Get Height of Texture
int Texture :: getHeight() {
	return image->getHeight();
}


// Binding Texture in OpenGL
void Texture::bind() {
	bind(GL_TEXTURE0);
}
// Binding Texture to Specific TextureUnit
void Texture::bind(GLenum TextureUnit) {

	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
}

// Unbind Texture from OpenGL
void Texture::unbind() {
	unbind(GL_TEXTURE0);
}
// Unbind Texture from Specific TextureUnit
void Texture::unbind(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}
