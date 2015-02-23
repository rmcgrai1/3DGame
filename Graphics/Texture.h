// Texture.h


#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <ImageMagick-6/Magick++.h>
using namespace std;

class Texture {
	public:
		Texture(Magick::Image mImg);
		Texture(const std::string&);
		Texture(GLenum, const std::string&);
		void bind();
		void bind(GLenum);
		bool load();
		bool loadFont();

		int getWidth();
		int getHeight();
		
	private:

		static int texNum;

		string m_fileName;

		int width;
		int height;
		GLenum m_textureTarget;
		GLuint m_textureObj;
		Magick::Image m_image;
		Magick::Blob m_blob;
};

#endif
