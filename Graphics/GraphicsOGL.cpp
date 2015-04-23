// GraphicsOGL.cpp
// Ryan McGrail

#define GL_GLEXT_PROTOTYPES

#include <unistd.h>
#include <chrono>
#include <stdlib.h>
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
#include "TextureController.h"
#include "../Primitives/Drawable.h"
#include "../Primitives/Updateable.h"
#include "FontController.h"
#include <ctime>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
#include "../Characters/Player.h"
#include "../Characters/NPC.h"
#include "../Environment/Tree.h"
#include "../Environment/Terrain.h"
#include "../menus/menu.h"
#include "../Environment/Shapes/PieceController.h"
#include "../Text/TextController.h"
#include "../Environment/PineTree.h"
#include "../Environment/Bush.h"
#include "../Environment/DirtPath.h"
#include "../Sound/SoundController.h"
#include "../Environment/Lamp.h"
#include "models/Model.h"
#include "models/Face.h"
#include "models/Pos3D.h"
#include "models/Mtl.h"
#include "../Functions/mat4.h"
#include "../Environment/Shapes/Piece.h"
using namespace std;
using namespace std::chrono;


TextController* tc;
DirtPath* dp;
GraphicsOGL* ogl;
void idleCallback() {

	ogl->idle();
}
void displayCallback() {

	ogl->display();
}


float shadowLocations[3*100];
int numShadows = 0;
int numLights = 0;
float lightRadii[100];
float lightLocations[3*100];
float lightColors[4*100];
mat4 modelMat = mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
Piece* testP;
Piece* pInst, *pRot;


GraphicsOGL :: GraphicsOGL(int argc, char* argv[]) {
	ogl = this;

	// Initialize Screen Resolution Variables
	resolution = new float[2];
	SCREEN_WIDTH = resolution[0] = 640;
	SCREEN_HEIGHT = resolution[1] = 480;

	avgFPS = 60;
	fps = 60;
	curProgram = 0;
	globalTime = 0;

	// Intialize 3D Variables
	initialize3D(argc, argv);
}

GraphicsOGL :: ~GraphicsOGL() {
	delete [] resolution;
}

Player* GraphicsOGL :: getPlayer() {
	return myPlayer;
}

Menu* GraphicsOGL :: getMenu() {
	return myMenu;
}

PieceController* GraphicsOGL :: getPieceController() {
	return AllStructures;
}


// IO
void GraphicsOGL :: logMessage(string str) {
	//cout << str << endl;
}


void GraphicsOGL :: setCulling(bool val) {
	(val) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void GraphicsOGL :: setDepthTest(bool val) {
	(val) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void GraphicsOGL :: initialize3D(int argc, char* argv[]) {

	srand(time(NULL));

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


		sc = new SoundController(argc,argv);

		//Load Resources, Create GraphicsOGL's Objects
		glCamera = new Camera();


		inputController = new InputController();
		fontController = new FontController();
		TextureController::initialize();
		shaderController = new ShaderController();


		for(int i = 0; i < 50; i++) {
			int s = 1000;
			float x, y, size;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);
			size = 1 + 2*(rand() % 100)/100;

			float cR, cG, cB;
			cR = .2 + .4*(rand() % 100)/100;
			cG = .6 + .4*(rand() % 100)/100;
			cB = .3 + .3*(rand() % 100)/100;
			new PineTree(x,y,size,cR,cG,cB);
		}

		for(int i = 0; i < 10; i++) {
			int s = 1000;
			float x, y;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);

			new Lamp(x,y, 1,1,0,.2);
		}

		for(int i = 0; i < 20; i++) {
			int s = 1000;
			float x, y, size;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);
			size = 1 + .5*rnd();

			float cR, cG, cB;
			cR = .2 + .2*rnd();
			cG = .6 + .4*rnd();
			cB = .3 + .5*rnd();

			new Bush(x,y,.25*size,cR,cG,cB);
		}


		myMenu = new Menu();
		AllStructures = new PieceController();
		//pauseMenu = new Menu();

		// Randomly Place NPCs
		for(int i = 0; i < 15; i++) {
			int s = 1000;
			float x, y, size;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);
			size = 1 + .5*rnd();

			float cR, cG, cB;
			cR = .2 + .2*rnd();
			cG = .6 + .4*rnd();
			cB = .3 + .5*rnd();

			new NPC(x,y,0);
		}

		dp = new DirtPath();
		for(int i = 0; i < 10; i++) {
			int s = 1000;
			float x, y, size = 32;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);

			dp->addPt(x, y, size);
		}

		// Initialize Basic Piece Blueprints
			Piece* pWall2x16 = new Piece(Piece::P_GROUP);
				pWall2x16->add3DBlock(-8,-8,0,-6,8,16);
			Piece* pWall2x32 = new Piece(Piece::P_GROUP);
				//pWall2x32->add3DBlock(-8,-8,0,-6,8,32);
				pWall2x32->add3DWall(-8,-8,0,-8,8,32);

			Piece* pDoorFrame2x16 = new Piece(Piece::P_GROUP);
				pDoorFrame2x16->add3DBlock(-8.5,-8,0,-5.5,-7,16);
				pDoorFrame2x16->add3DBlock(-8.5,7,0,-5.5,8,16);
				pDoorFrame2x16->add3DBlock(-8.5,-7,15,-5.5,7,16);

			Piece* pStairs16x16 = new Piece(Piece::P_GROUP);
			for(int i = 0; i < 8; i++) {
				float v, nV;
				v = 2*i;
				nV = 2*(i+1);
				//pStairs16x16->add3DBlock(v,-8,v,nV,8,nV);
				pStairs16x16->add3DFloor(-8+v,-8,-8+nV,8,v);
				pStairs16x16->add3DBlock(-8+v,-8,0,-8+nV,-6,nV+2);
				pStairs16x16->add3DBlock(-8+v,6,0,-8+nV,8,nV+2);
			}

			Piece* pStairs32x32 = new Piece(Piece::P_GROUP);
			float tS = 32, s = tS/2, n = tS/4, eH = tS/4;
			for(int i = 0; i < n; i++) {
				float v, nV;
				v = (tS/n)*i;
				nV = (tS/n)*(i+1);
				//pStairs16x16->add3DBlock(v,-8,v,nV,8,nV);
				pStairs32x32->add3DFloor(-s+v,-s,-s+nV,s,v);
				pStairs32x32->add3DBlock(-s+v,-s,0,-s+nV,-(s*.75),nV+eH);
				pStairs32x32->add3DBlock(-s+v,(s*.75),0,-s+nV,s,nV+eH);
			}

			Piece* pBlock16x2 = new Piece(Piece::P_GROUP);
				pBlock16x2->add3DFloor(-8,-8,8,8,0);
				//pBlock16x2->add3DBlock(-8,-8,-2,8,8,0);
			Piece* pBlock48x2 = new Piece(Piece::P_GROUP);
				pBlock48x2->add3DFloor(-24,-24,24,24,0);
				//pBlock48x2->add3DBlock(-24,-24,-2,24,24,0);
			Piece* pBlock48x16 = new Piece(Piece::P_GROUP);
				pBlock48x16->add3DBlock(-24,-8,-8,24,8,8);

		// Create Test Piece
			Piece* testP = new Piece(Piece::P_GROUP);
			testP->addPiece(pStairs16x16,-16,-16,-16,0,0,90);
			testP->addPiece(pStairs16x16,-16,16,-16,0,0,-90);
			testP->addPiece(pBlock16x2,-16,0,0);
			testP->addPiece(pStairs16x16,0,0,0);
			testP->addPiece(pBlock48x2,32,0,16);
			testP->addPiece(pBlock48x2,64,0,16);
	
			// Building
				testP->addPiece(pWall2x32,32,-16,16);
				testP->addPiece(pDoorFrame2x16,32,0,16);
				testP->addPiece(pWall2x16,32,0,32);
				testP->addPiece(pWall2x32,32,16,16);

			pInst = testP->instantiate();
				pInst->transformTranslation(1000,1000,270);
			pRot = pBlock48x16->instantiate();
				pRot->transformTranslation(1100,1000,270);

		
		myPlayer = new Player(1028,1028,0);
		
		terrain = new Terrain(2048*5,2048*5, 500, "Resources/Images/test.png",150);
		
		//Enables the text in the main menu
		tc = new TextController();
		tc->setText("Welcome to `Color:#FF0000`GAME TITLE``!\n\nExplore the land, kill monsters, and try to find the town.");

	//Set Up OpenGL Callbacks (Updating Functions...)
	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	//Start up Main Loop
	glutMainLoop();	
}

int GraphicsOGL :: isPCSlow() {
	return (avgFPS < 30);
}


void GraphicsOGL :: idle() {

	// Get Start Time
	fpsStart = getTime();

		pRot->transformRotationX(1);


		// Update All Updateable Objects
		Updateable :: updateAll(this, 1);

		sc->cleanAll();
		Updateable :: removeDestroyed();
		Drawable2 :: removeDestroyed();
		Instantiable :: removeDestroyed();
		Tree :: treeList.removeDestroyed();
		Character :: characterList.removeDestroyed();

		// Draw Current Frame
		glutPostRedisplay();


	// Get End Time
	fpsEnd = getTime();



	// Determine Time the Game Took to Process Current Frame
	double runTime = ((fpsEnd-fpsStart) + (drawEnd-drawStart))/1000.;

	// Calculate Time Required to Sleep to Stay at 60 FPS
	long sleepTime = 1000.*1000/60 - runTime;


	// Calculate FPS
	fps = 1000.*1000/(runTime);
	if(fps > 60)
		fps = 60;

	avgFPS = (fps + avgFPS)/2.;

	// If Sleep Time is Positive (Not Running Slow), Sleep for # Nanoseconds
	if(sleepTime > 0)
		usleep(sleepTime);
}

void GraphicsOGL :: display() {


	drawStart = getTime();

		

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glAlphaFunc(GL_GREATER, 0);


	globalTime += 1;
	

	passShaderUpdate();

	// DRAW WORLD

	setPerspective();

		// Draw All Drawable Objects
		terrain->drawFirst(this, 1);
		Drawable2 :: drawAll(this, 1);
		terrain->drawLast(this, 1);

	// DRAW HUD

	setOrtho();
		drawHealth(20,20, myPlayer->getHP(), myPlayer->getMaxHP());

		if(myPlayer->getTarget() != NULL)
			myPlayer->getTarget()->drawStatWindow(this,myPlayer->getTargetShift());

		setFont("8bit");
		// TEMPORARY FIX
		drawString(-20,-20,"0");

		string fpsStr = "FPS: ", dirStr = "Dir: ", posStr = "Pos: ";
			fpsStr = fpsStr + to_string(fps);
			dirStr = dirStr + to_string(getCamDir());
			posStr = posStr + to_string(myPlayer->getX()) + ", " + to_string(myPlayer->getY()) + ", " + to_string(myPlayer->getZ());



		float s = 1;
		drawStringScaled(0,400,s,s,fpsStr);
		drawStringScaled(0,420,s,s,dirStr);
		drawStringScaled(0,440,s,s,posStr);


	// Flush Graphics to Screen
	glFlush(); 
    	glutSwapBuffers();


	drawEnd = getTime();
}

//CAMERA FUNCTIONS
	Camera* GraphicsOGL :: getCamera() {
		return glCamera;
	}

	float GraphicsOGL :: getCamDir() {
		return glCamera->getCamDir();
	}

	void GraphicsOGL :: setProjectionPrep(float cX, float cY, float cZ, float tX, float tY, float tZ) {
		glCamera->setProjectionPrep(cX,cY,cZ,tX,tY,tZ);
	}

//DRAWING FUNCTIONS
	void GraphicsOGL :: setColor(int R, int G, int B) {

		glColor3ub(R,G,B);

		if(curProgram == 0)
			return;

		float color[4];
		color[0] = R/255.;
		color[1] = G/255.;
		color[2] = B/255.;
		color[3] = 1.;

		glUniform4fv(glGetUniformLocation(curProgram, "iColor"), 1, color);
	}

	void GraphicsOGL :: setColor(int R, int G, int B, int A) {

		glColor4ub(R,G,B,A);

		if(curProgram == 0)
			return;

		float color[4];
		color[0] = R/255.;
		color[1] = G/255.;
		color[2] = B/255.;
		color[3] = A/255.;

		glUniform4fv(glGetUniformLocation(curProgram, "iColor"), 1, color);
	}

	void GraphicsOGL :: drawPoint(float x, float y) {
		float depth = 0;
	
		// Create Point Primitive at Point (x,y)
		glBegin(GL_POINTS);
			glVertex3f(x, y, depth);
		glEnd();
	}

	void GraphicsOGL :: drawLine(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		// Create Line Primitive from (x1,y1) to (x2,y2)
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
		if(tex == NULL) {
			cout << "Attempted to draw NULL texture." << endl;
			return;
		}



		glEnable(GL_TEXTURE_2D);
		tex->bind();

		//glBegin(GL_QUADS);
		//glEnd();

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
		tex->unbind();
	}


//3D DRAWING

	// TRANSFORMATIONS
		void GraphicsOGL :: transformTranslation(float x, float y, float z) {

			// Translate in OpenGL
			glTranslatef(x, y, z);

			// Create Translation Matrix
			mat4 trMat(1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1);

			// Apply Translation Matrix to Model Matrix
			modelMat *= trMat;
		}
		void GraphicsOGL :: transformScale(float s) {
			transformScale(s, s, s);
		}
		void GraphicsOGL :: transformScale(float xS, float yS, float zS) {

			// Translate in OpenGL
			glScalef(xS, yS, zS);

			// Create Scale Matrix
			mat4 trMat(xS, 0, 0, 0,
				0, yS, 0, 0,
				0, 0, zS, 0,
				0, 0, 0, 1);

			// Apply Scale Matrix to Model Matrix
			modelMat *= trMat;
		}
		void GraphicsOGL :: transformRotationX(float angle) {
			glRotatef(angle, 1, 0, 0);

			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(1, 0, 0, 0,
				0, co, -si, 0,
				0, si, co, 0,
				0, 0, 0, 1);

			modelMat *= rot;
		}
		void GraphicsOGL :: transformRotationY(float angle) {
			glRotatef(angle, 0, 1, 0);

			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(co, 0, si, 0,
				0, 1, 0, 0,
				-si, 0, co, 0,
				0, 0, 0, 1);

			modelMat *= rot;
		}
		void GraphicsOGL :: transformRotationZ(float angle) {
			glRotatef(angle, 0, 0, 1);

			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(co, -si, 0, 0,
				si, co, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			modelMat *= rot;
		}
		void GraphicsOGL :: transformClear() {
			glLoadIdentity();
			modelMat.setIdentity();
		}


	// PRIMITIVES
		void GraphicsOGL :: draw3DSphere(float x, float y, float z, float r, int numPts) {
			draw3DSphere(x,y,z,r,numPts, NULL);
		}
		void GraphicsOGL :: draw3DSphere(float x, float y, float z, float r, int numPts, Texture* tex) {
			float z1, z2, xN1,yN1, xN2,yN2, zDir1, zDir2, xyN1,xyN2, zN1, zN2, dir;

			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}

			for(float i = 0; i < numPts; i++) {

				glBegin(GL_TRIANGLE_STRIP);

				for(float j = 0; j < numPts; j++) {

					float perc1, perc2;
					perc1 = .5-(i/numPts);
						perc1 = sin(3.14159*(-.5 + i/numPts));
					perc2 = .5-((i+1)/numPts);//sin(3.14159*(.5-((i+1)/numPts)));
						perc2 = sin(3.14159*(-.5 + (i+1)/numPts));

					zDir1 = 90*perc1;
					zDir2 = 90*perc2;

					xyN1 = calcLenX(1,zDir1);
					xyN2 = calcLenX(1,zDir2);
					zN1 = calcLenY(1,zDir1);
					zN2 = calcLenY(1,zDir2);

				
					dir = j/numPts*360;
						xN1 = calcLenX(1,dir)*xyN1;
						yN1 = calcLenY(1,dir)*xyN1;
						xN2 = calcLenX(1,dir)*xyN2;
						yN2 = calcLenY(1,dir)*xyN2;

					glTexCoord2f(j/numPts,i/numPts);
					glNormal3f(xN1,yN1,zN1);
						glVertex3f(x+xN1*r, y+yN1*r, z+zN1*r);
					glTexCoord2f(j/numPts,(i+1)/numPts);
					glNormal3f(xN2,yN2,zN2);
						glVertex3f(x+xN2*r, y+yN2*r, z+zN2*r);


					dir = (j+1)/numPts*360;
						xN1 = calcLenX(1,dir)*xyN1;
						yN1 = calcLenY(1,dir)*xyN1;
						xN2 = calcLenX(1,dir)*xyN2;
						yN2 = calcLenY(1,dir)*xyN2;

					glTexCoord2f((j+1)/numPts,i/numPts);
					glNormal3f(xN1,yN1,zN1);
						glVertex3f(x+xN1*r, y+yN1*r, z+zN1*r);
					glTexCoord2f((j+1)/numPts,(i+1)/numPts);
					glNormal3f(xN2,yN2,zN2);
						glVertex3f(x+xN2*r, y+yN2*r, z+zN2*r);
				}

				glEnd();
			}

			if(tex != NULL) {
				glDisable(GL_TEXTURE_2D);
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2) {
			draw3DWall(x1,y1,z1,x2,y2,z2,NULL);
		}
		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex) {
			draw3DWall(x1,y1,z1,x2,y2,z2,tex,1,1);
		}
		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex, float xRepeat, float yRepeat) {


			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}
			

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0); 
					glVertex3d(x1, y1, z1);
				glTexCoord2d(xRepeat, 0.0);
					glVertex3d(x2, y2, z1);
				glTexCoord2d(xRepeat, yRepeat);
					glVertex3d(x2, y2, z2);
				glTexCoord2d(0.0, yRepeat);
					glVertex3d(x1, y1, z2);
			glEnd();

			glDisable(GL_TEXTURE_2D);
			if(tex != NULL) {
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z) {
			draw3DFloor(x1,y1,x2,y2,z,NULL);
		}
		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z, Texture* tex) {
			draw3DFloor(x1,y1,x2,y2,z,tex,1,1);
		}
		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z, Texture* tex, float xRepeat, float yRepeat) {

			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}
			
			glAlphaFunc(GL_GREATER, 0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
			glBegin(GL_QUADS);
				glTexCoord2d(0.0, 0.0);
					glVertex3d(x1, y1, z);
				glTexCoord2d(xRepeat, 0.0);
					glVertex3d(x2, y1, z);
				glTexCoord2d(xRepeat, yRepeat);
					glVertex3d(x2, y2, z);
				glTexCoord2d(0.0, yRepeat);
					glVertex3d(x1, y2, z);
			glEnd();

			if(tex != NULL) {
				glDisable(GL_TEXTURE_2D);
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		void GraphicsOGL :: draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2) {
			// Create Line Primitive from (x1,y1,z1) to (x2,y2,z2)
			glBegin(GL_LINES);
				glVertex3f(x1, y1, z1);
				glVertex3f(x2, y2, z2);
			glEnd();
		}


		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2) {
			draw3DBlock(x1,y1,z1,x2,y2,z2,NULL);
		}
		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex) {
			draw3DBlock(x1,y1,z1,x2,y2,z2,tex,tex);
		}
		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2, Texture* texWall, Texture* texFloor) {
			draw3DWall(x1,y1,z1,x1,y2,z2,texWall);
			draw3DWall(x2,y1,z1,x2,y2,z2,texWall);
			draw3DWall(x1,y1,z1,x2,y1,z2,texWall);
			draw3DWall(x1,y2,z1,x2,y2,z2,texWall);
			draw3DFloor(x1,y1,x1,y2,z1,texFloor);
			draw3DFloor(x1,y1,x1,y2,z2,texFloor);
		}


		void GraphicsOGL :: draw3DCircle(float x, float y, float z, float rad, int sideNum) {
			draw3DPrism(x,y,z,rad,0,sideNum,NULL);
		}
		void GraphicsOGL :: draw3DCircle(float x, float y, float z, float rad, int sideNum, Texture* tex) {
			draw3DPrism(x,y,z,rad,0,sideNum,tex);
		}


		void GraphicsOGL :: draw3DCone(float x, float y, float z, float rad, float h, int sideNum) {
			draw3DCone(x,y,z,rad,h,sideNum,NULL);
		}
		void GraphicsOGL :: draw3DCone(float x, float y, float z, float rad, float h, int sideNum, Texture* tex) {
			draw3DFrustem(x,y,z,rad,0,h,sideNum,tex);
		}


		void GraphicsOGL :: draw3DFrustem(float x, float y, float z, float radBot, float radTop, float h, int sideNum) {
			draw3DFrustem(x,y,z,radBot,radTop,h,sideNum,NULL);
		}
		void GraphicsOGL :: draw3DFrustem(float x, float y, float z, float radBot, float radTop, float h, int sideNum, Texture* tex) {
			float ang = 45, dir, xN, yN;

			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}

			// Draw Top of Player Model
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(.5, .5);
				glNormal3f(0.,0.,1.);
					glVertex3f(x,y,z+h);

				for(int i = 0; i <= sideNum; i++) {
					dir = ang + 1.*i/sideNum*360;

					xN = calcLenX(1,dir);
					yN = calcLenY(1,dir);

					glTexCoord2f(.5 + .5*xN,.5 + .5*yN);
					glNormal3f(0.,0.,1.);
						glVertex3f(x+xN*radTop, y+yN*radTop, z+h);
				}
			glEnd();

			if(h != 0) {
				// Draw Bottom of Player Model
				glBegin(GL_TRIANGLE_FAN);
					glTexCoord2f(.5, .5);
					glNormal3f(0.,0.,-1.);
						glVertex3f(x,y,z);

					for(int i = 0; i <= sideNum; i++) {
						dir = ang + 1.*i/sideNum*360;

						xN = calcLenX(1,dir);
						yN = calcLenY(1,dir);

						glTexCoord2f(.5 + .5*xN,.5 + .5*yN);
						glNormal3f(0.,0.,-1.);
							glVertex3f(x+xN*radBot, y+yN*radBot, z);
					}
				glEnd();

				float zD, xy, zN;
				zD = calcPtDir(0,0,radBot-radTop,h)+90;
				xy = calcLenX(1,zD);
				zN = calcLenY(1,zD);

				// Draw Side Faces of Player Model
				for(int i = 0; i < sideNum; i++) {
					glBegin(GL_QUADS);

						dir = ang + 1.*i/sideNum*360;
							xN = calcLenX(1,dir);
							yN = calcLenY(1,dir);

						glTexCoord2f(0,0);
						glNormal3f(xy*xN,xy*yN,zN);
							glVertex3f(xN*radTop, yN*radTop, z+h);
						glTexCoord2f(0,1);
						glNormal3f(xy*xN,xy*yN,zN);
							glVertex3f(xN*radBot, yN*radBot, z);


						dir = ang + (i+1.)/sideNum*360;
							xN = calcLenX(1,dir);
							yN = calcLenY(1,dir);

						glTexCoord2f(1,1);
						glNormal3f(xy*xN,xy*yN,zN);
							glVertex3f(x+xN*radBot, y+yN*radBot, z);
						glTexCoord2f(1,0);
						glNormal3f(xy*xN,xy*yN,zN);
							glVertex3f(x+xN*radTop, y+yN*radTop, z+h);
					glEnd();
				}
			}

			if(tex != NULL) {
				glDisable(GL_TEXTURE_2D);
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		void GraphicsOGL :: draw3DPrism(float x, float y, float z, float rad, float h, int sideNum) {
			draw3DPrism(x,y,z,rad,h,sideNum,NULL);
		}
		void GraphicsOGL :: draw3DPrism(float x, float y, float z, float rad, float h, int sideNum, Texture* tex) {
			draw3DFrustem(x,y,z,rad,rad,h,sideNum,tex);
		}

	//3D MODEL
	void GraphicsOGL :: draw3DModel(Model *ModelToDraw) {
		Pos3D **Vertices = ModelToDraw->getVertices();
		Pos3D **TexCoords = ModelToDraw->getTexCoords();
		Pos3D **VNormals = ModelToDraw->getVNormals();
		Face **Faces = ModelToDraw->getFaces();
		int VertexCount = ModelToDraw->getVertexCount();
		int TexCoordCount = ModelToDraw->getTexCoordCount();
		int VNormalCount = ModelToDraw->getVNormalCount();
		int FaceCount = ModelToDraw->getFaceCount();
		
		Mtl *ThisMaterial;
		Face *ThisFace;
		Pos3D *Vertex;
		Pos3D *TexCoord;
		Pos3D *VNormal;
		int i,j;

		Texture *Tex = Faces[0]->getMaterial()->getTexture("map_Kd");
		Texture *PrevTex = Tex;
		if(Tex != NULL) {
			glEnable(GL_TEXTURE_2D);
			Tex->bind();
		}
		glBegin(GL_TRIANGLES);
			for(j = 0; j < FaceCount; j++) {
				ThisFace = Faces[j];
				ThisMaterial = ThisFace->getMaterial();
				Tex = ThisMaterial->getTexture("map_Kd");
				if(Tex != PrevTex) {
					glEnd();
					if(PrevTex != NULL) {
						glDisable(GL_TEXTURE_2D);
						PrevTex->unbind();
					}
					if(Tex != NULL) {
						glEnable(GL_TEXTURE_2D);
						Tex->bind();
					}
					glBegin(GL_TRIANGLES);
					PrevTex = Tex;
				}
				for(i=0;i<3;i++) {
					Vertex = ThisFace->getVertex(Vertices,VertexCount,i);
					TexCoord = ThisFace->getTexCoord(TexCoords,TexCoordCount,i);
					VNormal = ThisFace->getVNormal(VNormals,VNormalCount,i);
					glTexCoord2f(TexCoord->getX(),TexCoord->getY());
					glNormal3f(VNormal->getX(),VNormal->getY(),VNormal->getZ());
					glVertex3f(Vertex->getX(),Vertex->getY(),Vertex->getZ());
				}
			}
		glEnd();
		if(Tex != NULL) {
			glDisable(GL_TEXTURE_2D);
			Tex->unbind();
		}
	}


// Draw Health
	void GraphicsOGL :: drawHealth(float dX, float dY, float amt, float
maxAmt) {
		float s;
		if(maxAmt <= 20)
			s = 1;
		else
			s = .5;
		drawHealth(dX,dY,s,amt,maxAmt);
	}
	void GraphicsOGL :: drawHealth(float dX, float dY, float scale, float amt, float maxAmt) {
		if(amt < 0)
			amt = 0;

		Texture *h0, *h1, *h2, *h3, *h4, *cur;
		h0 = TextureController::getTexture("Heart0");
		h1 = TextureController::getTexture("Heart1");
		h2 = TextureController::getTexture("Heart2");
		h3 = TextureController::getTexture("Heart3");
		h4 = TextureController::getTexture("Heart4");
		
		float startX = dX;
		float s = 16;
		int lineSkip = 10/scale;
		for(int i = 0; i < maxAmt; i++) {

			if(i != 0 && i % lineSkip == 0) {
				dX = startX;
				dY += scale*(s+1);
			}

			if(amt == 0)
				cur = h0;
			else if(amt >= 1) {
				cur = h4;
				amt--;
			}
			else {
				if(amt >= .66)
					cur = h3;
				else if(amt >= .33)
					cur = h2;
				else
					cur = h1;
				amt = 0;
			}

			drawTextureScaled(dX,dY,scale*h0->getWidth()/s,scale*h0->getHeight()/s,cur);
			dX += scale*(s+1);
		}
	}

//SHADERS

	void GraphicsOGL :: setShaderVariable(string varName, float value) {
		glUniform1f(glGetUniformLocation(curProgram, varName.c_str()), value);
	}
	void GraphicsOGL :: setShaderInt(string varName, int value) {
		glUniform1i(glGetUniformLocation(curProgram, varName.c_str()), value);
	}
	void GraphicsOGL :: setShaderVec3(string varName, float array[3]) {
		glUniform3fv(glGetUniformLocation(curProgram, varName.c_str()), 1, array);
	}
	void GraphicsOGL :: setShaderMat4(string varName, mat4& matrix) {
		float mmFloats[16];
		matrix.getArray(mmFloats);

		glUniformMatrix4fv(glGetUniformLocation(curProgram, varName.c_str()), 1, GL_FALSE, mmFloats);
	}
	void GraphicsOGL :: passViewMatrix() {
		float camPos[3], camNorm[3];
		glCamera->getPosition(camPos);
		glCamera->getNormal(camNorm);

		float eyeX, eyeY, eyeZ, upX, upY, upZ, fX, fY, fZ;
		eyeX = camPos[0];
		eyeY = camPos[1];
		eyeZ = camPos[2];
		fX = camNorm[0];
		fY = camNorm[1];
		fZ = camNorm[2];
		upX = 0;
		upY = 0;
		upZ = 1;
		
		float lX, lY, lZ;
		lX = fX;
		lY = fY;
		lZ = fZ;

		// S = L x U
		float sX, sY, sZ, sN;
		sX = lY*upZ - lZ*upY;
		sY = lZ*upX - lX*upZ;
		sZ = lX*upY - lY*upX;
		sN = sqrt(sX*sX + sY*sY + sZ*sZ);
		sX /= sN;
		sY /= sN;
		sZ /= sN;

		// U' = S x L
		float uX, uY, uZ;
		uX = sY*lZ - sZ*lY;
		uY = sZ*lX - sX*lZ;
		uZ = sX*lY - sY*lX;

		mat4 viewMat(sX,uX,-lX,-eyeX,sY,uY,-lY,-eyeY,sZ,uZ,-lZ,-eyeZ,0,0,0,1);
		mat4 viewMat1(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
		mat4 viewMat2(1,0,0,-eyeX, 0,1,0,-eyeY, 0,0,1,-eyeZ, 0,0,0,1);

		viewMat = viewMat.transpose();

		setShaderMat4("viewMatrix", viewMat);
	}
	void GraphicsOGL :: passModelMatrix() {
		setShaderMat4("modelMatrix", modelMat);
	}
	void GraphicsOGL :: passShaderUpdate() {
		numShadows = 0;
		numLights = 0;

		float camPos[3], camX, camY, camFOV, camDir;
		glCamera->getPosition(camPos);
		camX = camPos[0];
		camY = camPos[1];
		camDir = glCamera->getCamDir();

		camFOV = 45;

		float curX, curY, curZ, curRad, curR, curG, curB, curA;

			for(int i = 0; i < Character::characterList.size(); i++) {
				Character* c = Character::characterList[i];
				curX = c->getX();
				curY = c->getY();

				if(!c->getOnScreen())
					continue;

				shadowLocations[numShadows*3+0] = curX;
				shadowLocations[numShadows*3+1] = curY;
				shadowLocations[numShadows*3+2] = 6;				
				numShadows++;

				// Add Light if Dying
				float f = c->getDestroyFraction();
				if(f != -1) {
					float flicker = .2*sqr(f)*(rnd()-.5);

					lightLocations[numLights*3+0] = curX + 4*f*(rnd()-.5);
					lightLocations[numLights*3+1] = curY + 4*f*(rnd()-.5);
					lightLocations[numLights*3+2] = c->getZ() + 4*f*(rnd()-.5);
					lightColors[numLights*4+0] = 1;
					lightColors[numLights*4+1] = 0;
					lightColors[numLights*4+2] = 0;
					lightColors[numLights*4+3] = f+flicker;
					lightRadii[numLights] = 25*(sqr(f)+flicker);
					numLights++;
				}
			}
			for(int i = 0; i < Tree::treeList.size(); i++) {
				Tree* t = Tree::treeList[i];

				if(!t->getHasShadow() || !t->getOnScreen())
					continue;

				curX = t->getX();
				curY = t->getY();
				curRad = 32*t->getSize();


				// BUG
				float aX, aY, toDir;
				aX = calcLenX(curRad,camDir+90);
				aY = calcLenY(curRad,camDir+90);
				toDir = min(abs(calcAngleDiff(calcPtDir(camX,camY,curX+aX,curY+aY),camDir)),abs(calcAngleDiff(calcPtDir(camX,camY,curX-aX,curY-aY),camDir)));

				
				shadowLocations[numShadows*3+0] = curX;
				shadowLocations[numShadows*3+1] = curY;
				shadowLocations[numShadows*3+2] = curRad;				
				numShadows++;
			}


		// SET UP LIGHT LIST
		////////////////////////////////////////////////////
		for(int i = 0; i < Lamp::lampList.size(); i++) {
			Lamp* l = Lamp::lampList[i];
			curX = l->getLightX();
			curY = l->getLightY();
			curZ = l->getLightZ();
			curR = l->getLightR();
			curG = l->getLightG();
			curB = l->getLightB();
			curA = l->getLightA();
			curRad = l->getLightRadius();

			// Light Coordinates
			lightLocations[numLights*3+0] = curX;
			lightLocations[numLights*3+1] = curY;
			lightLocations[numLights*3+2] = curZ;
			lightColors[numLights*4+0] = curR;
			lightColors[numLights*4+1] = curG;
			lightColors[numLights*4+2] = curB;
			lightColors[numLights*4+3] = curA;
			lightRadii[numLights] = curRad;
			numLights++;
		}
	}
	// Function for Passing Lights to Shader
	void GraphicsOGL :: passShaderLights() {
		glUniform3fv(glGetUniformLocation(curProgram, "lights"), 100, lightLocations);
		glUniform4fv(glGetUniformLocation(curProgram, "lightColors"), 100, lightColors);
		glUniform1fv(glGetUniformLocation(curProgram, "lightRads"), 100, lightRadii);
		glUniform1i(glGetUniformLocation(curProgram, "lightNum"), numLights);
	}
	// Function for Passing Shadows to Shader
	void GraphicsOGL :: passShaderShadows() {
		glUniform3fv(glGetUniformLocation(curProgram, "shadows"), 100, shadowLocations);
		glUniform1i(glGetUniformLocation(curProgram, "shadowNum"),numShadows);
	}
	void GraphicsOGL :: passShaderPath() {
		
		glUniform3fv(glGetUniformLocation(curProgram, "pathPts"), 100, dp->pts);
		glUniform1i(glGetUniformLocation(curProgram, "pathPtNum"), dp->numPts);
	}

	void GraphicsOGL :: disableShaders() {
		// TOTALLY BREAKS TEXTURES
		glUseProgram(0);
		//textureController->getTexture("Noise")->unbind(GL_TEXTURE2);
	}

	void GraphicsOGL :: enableShader(string name) {
		curShader = shaderController->getShader(name);

		Texture* noiseTex = TextureController::getTexture("Noise");

		// Set Current Shader Program
		curProgram = curShader->getProgram();

		// Enable Current Shader
		glUseProgram(curProgram);

		// ** Pass Screen Resolution and Time Value (Used in Animations) to Shader
		glUniform2fv(glGetUniformLocation(curProgram, "iResolution"), 1, resolution);			
    		glUniform1f(glGetUniformLocation(curProgram, "iGlobalTime"), globalTime/50.);      
		glUniform1f(glGetUniformLocation(curProgram, "iRadius"), 0);



		// Get Camera Position and Direction
		float camNormal[3], camPos[3], sCamPos[3], camDir[3];
		glCamera->getNormal(camNormal);
		glCamera->getPosition(camPos);
		glCamera->getShaderPosition(sCamPos);
		glCamera->getDirection(camDir);

		// ** Pass Camera Position and Direction to Shader
		glUniform3fv(glGetUniformLocation(curProgram, "camNormal"), 1, camNormal);		
		glUniform3fv(glGetUniformLocation(curProgram, "rCamPos"), 1, camPos);
		glUniform3fv(glGetUniformLocation(curProgram, "iCamPos"), 1, sCamPos);
		glUniform3fv(glGetUniformLocation(curProgram, "iCamDir"), 1, camDir);  

		glUniform1f(glGetUniformLocation(curProgram, "seaLevel"), terrain->getSeaLevel());  

		// Pass Texture(s) to Shader
		glUniform1i(glGetUniformLocation(curProgram, "Texture0"), 0);
    		glUniform1i(glGetUniformLocation(curProgram, "Texture1"), 1);
    		glUniform1i(glGetUniformLocation(curProgram, "Texture2"), 3);
    		glUniform1i(glGetUniformLocation(curProgram, "noiseTex"), 2);
			//noiseTex->bind(GL_TEXTURE2);
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
		if(t == NULL) {
			cout << "Attempted to draw a character not present in the font." << endl;
			return 0;
		}

		if(c == 'y' || c == 'g' || c == 'j' || c == 'p' || c == 'q')
			y += .25*t->getHeight()*yS;

		drawTextureScaled(x, y, xS, yS, t);
		return t->getWidth()*xS;
	}

	void GraphicsOGL :: drawString(float x, float y, string str) {
		drawStringScaled(x,y,1,1,str);
	}

	void GraphicsOGL :: drawStringScaled(float x, float y, float xS, float yS, string str) {
		int len = str.length();
		char c;

		float s = curFont->getWidth(), e = -1;

		float dX = x, dY = y;

		for(int i = 0; i < len; i++) {
			c = str[i];

			if(c == '\n') { 
				dY += s*yS + e*yS;
				dX = x;
			}
			else if(c == ' ')
				dX += s*xS + e*xS;
			else if(islower(c))
				dX += drawCharScaled(dX,dY + (s*yS*.25), xS,yS*.75, c) + e*xS;
			else
				dX += drawCharScaled(dX,dY, xS, yS, c) + e*xS;
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
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH);
	glDisable(GL_LIGHTING);
}


// ACCESSOR/MUTATOR
	//Get Screen Width
	int GraphicsOGL :: getScreenWidth() {
		return SCREEN_WIDTH;
	}	

	//Get Screen Height
	int GraphicsOGL :: getScreenHeight() {
		return SCREEN_HEIGHT;
	}

	InputController* GraphicsOGL :: getInputController() {
		return inputController;
	}
	Heightmap* GraphicsOGL :: getHeightmap() {
		return terrain->getHeightmap();
	}
	TextController* GraphicsOGL :: getTextController() {
		return tc;
	}
	SoundController* GraphicsOGL :: getSoundController() {
		return sc;
	}

