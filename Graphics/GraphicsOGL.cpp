// GraphicsOGL.cpp


#define GL_GLEXT_PROTOTYPES

#include <unistd.h>
#include <chrono>
#include <cctype>
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "Image.h"
#include "Camera.h"
#include "GraphicsOGL.h"
#include "Shader.h"
#include "Font.h"
#include "../IO/InputController.h"
#include "ShaderController.h"
#include "../Primitives/Drawable.h"
#include "../Primitives/Updateable.h"
#include "FontController.h"
#include "../Functions/Math2D.h"
#include <ctime>
#include "../Environment/Heightmap.h"

#include "../Characters/Player.h"
using namespace std;
using namespace std::chrono;


bool isDrawing = false;

Player* p;
Texture* GraphicsOGL::tst;

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

	fps = 1;

	curProgram = 0;
	globalTime = 0;

	initialize3D(argc, argv);
}

GraphicsOGL :: ~GraphicsOGL() {
	delete [] resolution;
}

void GraphicsOGL :: initialize3D(int argc, char* argv[]) {

	//Initialize OpenGL
	glutInit(&argc, argv);

	//Initialize OpenGL Window
	glutInitDisplayMode(GLUT_DEPTH|GLUT_SINGLE|GLUT_RGBA); 
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Game"); 	

	//Set Up View Port for Window
	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0, -3,1000);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);


		p = new Player(0,0,0);
		//curHeightmap = new Heightmap(1028,1028,1/32.);
		curHeightmap = new Heightmap(2048,2048,"Resources/Images/test.png");
		tst = new Texture("Resources/Images/test.png",false);
		//Load Resources, Create GraphicsOGL's Objects
		glCamera = new Camera();
		inputController = new InputController();
		fontController = new FontController();
		shaderController = new ShaderController();

	//Set Up OpenGL Callbacks (Updating Functions...)
	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Start up Main Loop
	glutMainLoop();
}

//Get Screen Width
int GraphicsOGL :: getScreenWidth() {
	return SCREEN_WIDTH;
}

//Get Screen Height
int GraphicsOGL :: getScreenHeight() {
	return SCREEN_HEIGHT;
}

int GraphicsOGL :: getMouseX() {
	return inputController->getMouseX();
}

int GraphicsOGL :: getMouseY() {
	return inputController->getMouseY();
}


bool GraphicsOGL :: getShift() {
	return inputController->getShift();
}
float GraphicsOGL :: getWASDDir() {
	return inputController->getWASDDir();
}

Heightmap* GraphicsOGL :: getHeightmap() {
	return curHeightmap;
}

void GraphicsOGL :: idle() {

	//Get Start Time
	fpsStart = getTime();

		Updateable :: updateAll(this, 1);

		//Draw Current Frame
		glutPostRedisplay();

	fpsEnd = getTime();



	double runTime = (fpsEnd-fpsStart)/1000.;
	long sleepTime = 1000.*1000/60 - runTime;

	cout << 1000.*1000/60 << ": " << runTime << ", " << sleepTime << endl;


	fps = 1000.*1000/(runTime);
	if(fps > 60)
		fps = 60;


	if(sleepTime > 0)
		usleep(sleepTime);

	isDrawing = false;
}

void GraphicsOGL :: display() {


	long start = getTime();

	


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glAlphaFunc(GL_GREATER, 0);


	setFont("8bit");

	globalTime += 1;


	
	glColor3f(1,1,1);


	setPerspective();
		draw3DWall(-16,0,32,16,0,0,NULL);

		//enableShader("GalaxyTexture");	
		Drawable2 :: drawAll(this, 1);
	setOrtho();

			fillPolygon(getMouseX(),getMouseY(),30,3, globalTime);
			//fillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
		//disableShaders();

		string fpsStr = "FPS: ", dirStr = "Dir: ";
			fpsStr = fpsStr + to_string(fps);
			dirStr = dirStr + to_string(getCamDir());

		drawStringScaled(0,0,.65,.65,fpsStr);
		drawStringScaled(0,20,.65,.65,dirStr);

	glFlush(); 
    	glutSwapBuffers();


	long end = getTime();

	cout << (end-start)/1000. << endl;
}

//CAMERA FUNCTIONS
	float GraphicsOGL :: getCamDir() {
		return glCamera->getCamDir();
	}

	void GraphicsOGL :: setProjectionPrep(float cX, float cY, float cZ, float tX, float tY, float tZ) {
		glCamera->setProjectionPrep(cX,cY,cZ,tX,tY,tZ);
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

	void GraphicsOGL :: drawCircle(float x, float y, float r, int vertNum) {
		float depth = 0, dir, xN, yN;
	
		glBegin(GL_LINE_LOOP);
			for(float i = 0; i < vertNum; i++) {
				dir = i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	void GraphicsOGL :: fillCircle(float x, float y, float r, int vertNum) {
		float depth = 0, dir, xN, yN;
	
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(.5,.5);
				glVertex3f(x, y, depth);
			for(float i = 0; i < vertNum+1; i++) {
				dir = i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	void GraphicsOGL :: drawPolygon(float x, float y, float r, int vertNum, float angle) {
		float depth = 0, dir, xN, yN;
	
		glBegin(GL_LINE_LOOP);
			for(float i = 0; i < vertNum; i++) {
				dir = angle + i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	void GraphicsOGL :: fillPolygon(float x, float y, float r, int vertNum, float angle) {
		float depth = 0, dir, xN, yN;
	
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(.5,.5);
				glVertex3f(x, y, depth);
			for(float i = 0; i < vertNum+1; i++) {
				dir = angle + i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	void GraphicsOGL :: drawTexture(float x, float y, Texture* tex) {
		
		drawTextureScaled(x, y, 1, 1, tex);
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
		glBindTexture(GL_TEXTURE_2D, 0);
	}

//3D DRAWING

	void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex) {

			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				
				tex->bind();
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
						
			/*glColor4f(1f, 1f, 1f, (float) alpha);
			
			gl.glTranslated(sx+xScale*x,sy+yScale*y,sz+zScale*z);
			gl.glRotated(rotZ, 0, 0, 1);
			gl.glRotated(rotY, 0, 1, 0);
			gl.glRotated(rotX, 1, 0, 0);
			
			gl.glScalef(xScale, yScale, zScale);*/
			
			glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0); 	
					glVertex3d(x1, y1, z1);
				glTexCoord2d(1.0, 0.0);
					glVertex3d(x2, y2, z1);
				glTexCoord2d(1.0, 1.0);
					glVertex3d(x2, y2, z2);
				glTexCoord2d(0.0, 1.0);
					glVertex3d(x1, y1, z2);
			glEnd();
			
			//glLoadIdentity();
			
			
			//glColor4f(1f, 1f, 1f, 1f);

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z, Texture* tex) {

			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				
				tex->bind();
				
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
						
			/*glColor4f(1f, 1f, 1f, (float) alpha);
			
			gl.glTranslated(sx+xScale*x,sy+yScale*y,sz+zScale*z);
			gl.glRotated(rotZ, 0, 0, 1);
			gl.glRotated(rotY, 0, 1, 0);
			gl.glRotated(rotX, 1, 0, 0);
			
			gl.glScalef(xScale, yScale, zScale);*/
			
			glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0);
					glVertex3d(x1, y1, z);
				glTexCoord2d(1.0, 0.0);
					glVertex3d(x2, y1, z);
				glTexCoord2d(1.0, 1.0);
					glVertex3d(x2, y2, z);
				glTexCoord2d(0.0, 1.0);
					glVertex3d(x1, y2, z);
			glEnd();
			
			
			//glLoadIdentity();
			
			
			//glColor4f(1f, 1f, 1f, 1f);

		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

//SHADERS

	void GraphicsOGL :: disableShaders() {
		glUseProgram(0);
	}

	void GraphicsOGL :: enableShader(string name) {
		enableShader(shaderController->getProgram(name));
	}

	void GraphicsOGL :: enableShader(GLuint program) {
		glUseProgram(program);

		glUniform2fv(glGetUniformLocation(program, "iResolution"), 1, resolution);			
    		glUniform1f(glGetUniformLocation(program, "iGlobalTime"), globalTime/50.);      
		glUniform1f(glGetUniformLocation(program, "iRadius"), 3);        
	}

	void GraphicsOGL :: setCurrentTextureSize(int w, int h) {
		if(curProgram == 0)
			return;

		float si[2];
		si[0] = w;
		si[1] = h;

		glUniform2fv(glGetUniformLocation(curProgram, "iSize"), 1, si);				
	}

//TEXT DRAWING
	void GraphicsOGL :: setFont(string name) {
		curFont = fontController->getFont(name);
	}

	float GraphicsOGL :: drawChar(float x, float y, char c) {
		return drawCharScaled(x, y, 1, 1, c);
	}

	float GraphicsOGL :: drawCharScaled(float x, float y, float xS, float yS, char c) {
		Texture* t = curFont->getChar(c);

		drawTextureScaled(x, y, xS, yS, t);
		return t->getWidth()*xS;
	}

	void GraphicsOGL :: drawString(float x, float y, string str) {
		drawStringScaled(x,y,1,1,str);
	}

	void GraphicsOGL :: drawStringScaled(float x, float y, float xS, float yS, string str) {
		int len = str.length();
		char c;

		float s = 16;

		float dX = x, dY = y;

		for(int i = 0; i < len; i++) {
			c = str[i];

			if(c == '\n') { 
				dY += s*yS + 1;
				dX = x;
			}
			else if(c == ' ')
				dX += s*xS + 1;
			else if(islower(c))
				dX += drawCharScaled(dX,dY + (s*yS*.25), xS,yS*.75, c) + 1;
			else
				dX += drawCharScaled(dX,dY, xS, yS, c) + 1;
		}
	}

//Graphics Mode
void GraphicsOGL :: setOrtho() {
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1000, 1000);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH);
}

void GraphicsOGL :: setPerspective() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glCamera->setProjection(this);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH);
}

unsigned long GraphicsOGL :: getTime() {

	nanoseconds ms = duration_cast< nanoseconds >(
 		high_resolution_clock::now().time_since_epoch()
	);

	return ms.count();
}
