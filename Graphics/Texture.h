// Texture.h


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
		Texture(string);
		Texture(string, bool);
		Texture(string, const string&);
		Texture(string, const string&, bool);


		string getName();
		int getWidth();
		int getHeight();

		void bind();
		void bind(GLenum);

		void unbind();
		void unbind(GLenum);
		
	private:

		static int texNum;

		string name;
		string fileName;

		GLuint m_textureObj;
		Image* image;
};

#endif
