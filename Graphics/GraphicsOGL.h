// GraphicsOGL.h

#ifndef GRAPHICSOGL_H
#define GRAPHICSOGL_H

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "Font.h"

class GraphicsOGL {
	public:
		GraphicsOGL(int, char* []);
		~GraphicsOGL();

		void idle();
		void display();
		
		//DRAWING
			void setColor(int,int,int);
			void drawPoint(float,float);
			void drawLine(float,float,float,float);
			void drawRect(float,float,float,float);
			void fillRect(float,float,float,float);
			void drawTexture(float, float, Texture*);
			void drawTextureScaled(float, float, float, float, Texture*);
			float drawChar(float, float, char, Font*);
			float drawCharScaled(float, float, float, float, char, Font*);
			void drawString(float, float, string, Font*);
			void drawStringScaled(float, float, float, float, string, Font*);

		//SHADERS
			void enableShader(GLuint);
			void setCurrentTextureSize(int,int);

	private:
		void initialize3D(int, char* []);

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;

		//Shader Variables
			GLuint curProgram;
			float* resolution;
			float globalTime;

		static Texture* tst;
};

#endif
