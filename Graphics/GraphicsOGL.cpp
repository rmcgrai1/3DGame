// GraphicsOGL.cpp


#define GL_GLEXT_PROTOTYPES

#include <cctype>
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "GraphicsOGL.h"
#include "Shader.h"
#include "Font.h"
using namespace std;


Font* f;
Shader* sh;
Texture* GraphicsOGL::tst = new Texture("Resources/Images/test.png");

GraphicsOGL* ogl;
void idleCallback() {
	ogl->idle();
}
void displayCallback() {

	ogl->display();
}


GraphicsOGL :: GraphicsOGL(int argc, char* argv[]) {
	ogl = this;

	resolution = new float[2];

	SCREEN_WIDTH = resolution[0] = 640;
	SCREEN_HEIGHT = resolution[1] = 480;

	curProgram = 0;
	globalTime = 0;

	initialize3D(argc, argv);
}

GraphicsOGL :: ~GraphicsOGL() {
	delete [] resolution;
}

void GraphicsOGL :: initialize3D(int argc, char* argv[]) {
	Magick::InitializeMagick(*argv);    
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA); 
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Game"); 	

	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0, -3,1000);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);


		tst->load();
		sh = new Shader("Galaxy");
		f = new Font("8bit", false);


	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
}

void GraphicsOGL :: idle() {
	// draw current frame
	glutPostRedisplay();
}

void GraphicsOGL :: display() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glAlphaFunc(GL_GREATER, 0);

	globalTime += .0001;


	enableShader(sh->getProgram());
	//drawTextureScaled(0,0,10,10,tst);
	drawStringScaled(0,0,.65,.65,"Hello, Shaquille. We are set!",f);

	glFlush(); 
    	glutSwapBuffers();
}


//DRAWING FUNCTIONS
	void GraphicsOGL :: setColor(int R, int G, int B) {
		glColor3i(R, G, B);
	}

	void GraphicsOGL :: drawPoint(float x, float y) {
		float depth = 0;
	
		glBegin(GL_POINTS);
			glVertex3f(x, y, depth);
		glEnd();
	}

	void GraphicsOGL :: drawLine(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		glBegin(GL_LINES);
			glVertex3f(x1, y1, depth);
			glVertex3f(x2, y2, depth);
		glEnd();
	}

	void GraphicsOGL :: drawRect(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		glBegin(GL_LINE_LOOP);
			glTexCoord2f(0,0);
				glVertex3f(x1, y1, depth);
			glTexCoord2f(1,0);
				glVertex3f(x2, y1, depth);
			glTexCoord2f(1,1);
				glVertex3f(x2, y2, depth);
			glTexCoord2f(0,1);
				glVertex3f(x1, y2, depth);
		glEnd();
	}

	void GraphicsOGL :: fillRect(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
				glVertex3f(x1, y1, depth);
			glTexCoord2f(1,0);
				glVertex3f(x2, y1, depth);
			glTexCoord2f(1,1);
				glVertex3f(x2, y2, depth);
			glTexCoord2f(0,1);
				glVertex3f(x1, y2, depth);
		glEnd();
	}

	void GraphicsOGL :: drawTexture(float x, float y, Texture* tex) {
		glEnable(GL_TEXTURE_2D);
		tex->bind();


		float depth = 0, w, h;
		w = tex->getWidth();
		h = tex->getHeight();

		setCurrentTextureSize(w,h);
	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
				glVertex3f(x, y, depth);
			glTexCoord2f(1,0);
				glVertex3f(x+w, y, depth);
			glTexCoord2f(1,1);
				glVertex3f(x+w, y+h, depth);
			glTexCoord2f(0,1);
				glVertex3f(x, y+h, depth);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void GraphicsOGL :: drawTextureScaled(float x, float y, float xS, float yS, Texture* tex) {
		glEnable(GL_TEXTURE_2D);
		tex->bind();


		float depth = 0, w, h;
		w = xS*tex->getWidth();
		h = yS*tex->getHeight();
	
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
				glVertex3f(x, y, depth);
			glTexCoord2f(1,0);
				glVertex3f(x+w, y, depth);
			glTexCoord2f(1,1);
				glVertex3f(x+w, y+h, depth);
			glTexCoord2f(0,1);
				glVertex3f(x, y+h, depth);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void GraphicsOGL :: enableShader(GLuint program) {
		glUseProgram(program);

		glUniform2fv(glGetUniformLocation(program, "iResolution"), 1, resolution);			
    		glUniform1f(glGetUniformLocation(program, "iGlobalTime"), globalTime/50.);        
	}

	void GraphicsOGL :: setCurrentTextureSize(int w, int h) {
		if(curProgram == 0)
			return;

		float si[2];
		si[0] = w;
		si[1] = h;

		glUniform2fv(glGetUniformLocation(curProgram, "iSize"), 1, si);				
	}

	float GraphicsOGL :: drawChar(float x, float y, char c, Font* ft) {
		return drawCharScaled(x, y, 1, 1, c, ft);
	}

	float GraphicsOGL :: drawCharScaled(float x, float y, float xS, float yS, char c, Font* ft) {
		Texture* t = ft->getChar(c);

		drawTextureScaled(x, y, xS, yS, t);
		return t->getWidth()*xS;
	}

	void GraphicsOGL :: drawString(float x, float y, string str, Font* ft) {
		drawStringScaled(x,y,1,1,str,ft);
	}

	void GraphicsOGL :: drawStringScaled(float x, float y, float xS, float yS, string str, Font* ft) {
		int len = str.length();
		char c;

		for(int i = 0; i < len; i++) {
			c = str[i];

			if(c == ' ')
				x += 16*xS + 1;
			else if(islower(c))
				x += drawCharScaled(x,y + (16*yS*.25), xS*.75,yS*.75, c, ft) + 1;
			else
				x += drawCharScaled(x,y, xS, yS, c, ft) + 1;
		}
	}
