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


// Callbacks for Glut
GraphicsOGL* ogl;
void idleCallback() {
	ogl->idle();
}
void displayCallback() {
	ogl->display();
}

// Initialize Global Variables
TextController* tc;
DirtPath* dp;
float shadowLocations[3*100];
int numShadows = 0;
int numLights = 0;
float lightRadii[100];
float lightLocations[3*100];
float lightColors[4*100];
mat4 modelMat = mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
Piece* testP;
Piece* pInst, *pRot;


// Constructor
GraphicsOGL :: GraphicsOGL(int argc, char* argv[]) {
	ogl = this;

	// Initialize Screen Resolution Variables
	resolution = new float[2];
	SCREEN_WIDTH = resolution[0] = 640;
	SCREEN_HEIGHT = resolution[1] = 480;

	// Initialize FPS Variables
	avgFPS = 60;
	fps = 60;
	
	// Initialize Shader Vars
	curProgram = 0;
	globalTime = 0;

	// Intialize 3D Variables
	initialize3D(argc, argv);
}

// Deconstructor
GraphicsOGL :: ~GraphicsOGL() {
	delete [] resolution;
}

// Getting Player
Player* GraphicsOGL :: getPlayer() {
	return myPlayer;
}

// Getting Menu
Menu* GraphicsOGL :: getMenu() {
	return myMenu;
}

// Getting PieceController
PieceController* GraphicsOGL :: getPieceController() {
	return AllStructures;
}


// Logging Messages
void GraphicsOGL :: logMessage(string str) {
	//cout << str << endl;
}

// Enabling Backface Culling in OpenGL
void GraphicsOGL :: setCulling(bool val) {
	(val) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

// Enabling Depth-Testing for Faces
void GraphicsOGL :: setDepthTest(bool val) {
	(val) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

// Initialization of 3D Resources, Objects
void GraphicsOGL :: initialize3D(int argc, char* argv[]) {

	// Seed Random Number Generator
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

	// Enable Depth-Testing, Alpha-Testing, and Textures
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);

		// Initialize Sound Controller
		sc = new SoundController(argc,argv);

		//Load Resources, Create GraphicsOGL's Objects
		glCamera = new Camera();

		// Initialize Various Resource Controllers
		inputController = new InputController();
		fontController = new FontController();
		TextureController::initialize();
		shaderController = new ShaderController();

		// Create Random Pine Trees
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

		// Create Random Lamps
		for(int i = 0; i < 10; i++) {
			int s = 1000;
			float x, y;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);

			new Lamp(x,y, 1,1,0,.2);
		}

		// Create Random Bushes
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

		// Create Menu
		myMenu = new Menu();
		// Create Piece Controller
		AllStructures = new PieceController();

		// Randomly Place NPCs in Environment
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

		// Initialize Dirt Path, Random Points
		dp = new DirtPath();
		for(int i = 0; i < 10; i++) {
			int s = 1000;
			float x, y, size = 32;
			x = 1028 + (rand() % s - s/2.);
			y = 1028 + (rand() % s - s/2.);

			dp->addPt(x, y, size);
		}

		// Initialize Basic Piece Blueprints
			// 2x16x16 Wall
			Piece* pWall2x16 = new Piece(Piece::P_GROUP);
				pWall2x16->add3DBlock(-8,-8,0,-6,8,16);
			// 2x16x32 Wall
			Piece* pWall2x32 = new Piece(Piece::P_GROUP);
				pWall2x32->add3DWall(-8,-8,0,-8,8,32);
			// 2x16x16 Door Frame
			Piece* pDoorFrame2x16 = new Piece(Piece::P_GROUP);
				pDoorFrame2x16->add3DBlock(-8.5,-8,0,-5.5,-7,16);
				pDoorFrame2x16->add3DBlock(-8.5,7,0,-5.5,8,16);
				pDoorFrame2x16->add3DBlock(-8.5,-7,15,-5.5,7,16);

			// 16x16x16 Stairs
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
			// 32x32x32 Stairs
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

			// 16x16x2 Block
			Piece* pBlock16x2 = new Piece(Piece::P_GROUP);
				pBlock16x2->add3DFloor(-8,-8,8,8,0);
			// 48x48x2 Block
			Piece* pBlock48x2 = new Piece(Piece::P_GROUP);
				pBlock48x2->add3DFloor(-24,-24,24,24,0);
			// 48x16x16 Block
			Piece* pBlock48x16 = new Piece(Piece::P_GROUP);
				pBlock48x16->add3DBlock(-24,-8,-8,24,8,8);

		// Create Test Piece
			Piece* testP = new Piece(Piece::P_GROUP);
			
			// Staircaes
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

			// Instantiate Test House, Position
			pInst = testP->instantiate();
				pInst->transformTranslation(1000,1000,270);
			// Instantiate Rotating Block, Position
			pRot = pBlock48x16->instantiate();
				pRot->transformTranslation(1100,1000,270);

		// Create Player
		myPlayer = new Player(1028,1028,0);
		
		// Create Terrain
		terrain = new Terrain(2048*5,2048*5, 500, "Resources/Images/test.png",150);
		
		//Enables the text in the main menu
		tc = new TextController();
		tc->setText("Welcome to `Color:#FF0000`GAME TITLE``!\n\nExplore the land, kill monsters, and try to find the town.");

	//Set Up OpenGL Callbacks (Updating Functions...)
	glutIdleFunc(idleCallback);
	glutDisplayFunc(displayCallback);

	// Clear Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	//Start up Main Loop
	glutMainLoop();	
}

// Check If FPS < 30, PC is Too Slow (Hardwired to False to Prevent Flickering!)
int GraphicsOGL :: isPCSlow() {
	return false; //(avgFPS < 30);
}

// Updating Script for OpenGL
void GraphicsOGL :: idle() {

	// Get Start Time
	fpsStart = getTime();

		// Rotate Spinning Block
		pRot->transformRotationX(1);


		// Update All Updateable Objects
		Updateable :: updateAll(this, 1);

		// Clean Finished Sounds
		sc->cleanAll();
		// Remove Destroyed Instances of Objects
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
// Drawing Script for OpenGL
void GraphicsOGL :: display() {

	// Starting time for Draw Script (For Calculating FPS)
	drawStart = getTime();

	// Clear Background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glAlphaFunc(GL_GREATER, 0);

	// Increment Time (For Time-based Shaders)
	globalTime += 1;
	
	// Update Values to Pass to Shaders
	passShaderUpdate();

	// DRAW WORLD

	// Enable 3D Drawing
	setPerspective();

		// Draw All Drawable Objects
		terrain->drawFirst(this, 1);
		Drawable2 :: drawAll(this, 1);
		terrain->drawLast(this, 1);

	// DRAW HUD

	// Enable 2D Drawing
	setOrtho();
		// Draw Player Healthbar
		drawHealth(20,20, myPlayer->getHP(), myPlayer->getMaxHP());

		// If Player is Targeting Enemy, Draw Stats Window
		if(myPlayer->getTarget() != NULL)
			myPlayer->getTarget()->drawStatWindow(this,myPlayer->getTargetShift());

		// Set Font
		setFont("8bit");

		// Create Strings for Various Info
		string fpsStr = "FPS: ", dirStr = "Dir: ", posStr = "Pos: ";
			fpsStr = fpsStr + to_string(fps);
			dirStr = dirStr + to_string(getCamDir());
			posStr = posStr + to_string(myPlayer->getX()) + ", " + to_string(myPlayer->getY()) + ", " + to_string(myPlayer->getZ());

		float s = 1;
		// Draw Strings to Screen
		drawStringScaled(0,400,s,s,fpsStr);
		drawStringScaled(0,420,s,s,dirStr);
		drawStringScaled(0,440,s,s,posStr);


	// Flush Graphics to Screen
	glFlush(); 
    	glutSwapBuffers();

	// Get Ending Time in Draw Script for FPS
	drawEnd = getTime();
}

//CAMERA FUNCTIONS
	// Get Camera
	Camera* GraphicsOGL :: getCamera() {
		return glCamera;
	}
	// Get Camera Direction
	float GraphicsOGL :: getCamDir() {
		return glCamera->getCamDir();
	}
	// Prepare for 3D Projection
	void GraphicsOGL :: setProjectionPrep(float cX, float cY, float cZ, float tX, float tY, float tZ) {
		glCamera->setProjectionPrep(cX,cY,cZ,tX,tY,tZ);
	}

//DRAWING FUNCTIONS
	// Setting Color RGB
	void GraphicsOGL :: setColor(int R, int G, int B) {
		// Set Color in OpenGL
		glColor3ub(R,G,B);

		// If No Shader Enabled, Quit
		if(curProgram == 0)
			return;

		float color[4];
		color[0] = R/255.;
		color[1] = G/255.;
		color[2] = B/255.;
		color[3] = 1.;

		// Pass Color to Shader as Array
		glUniform4fv(glGetUniformLocation(curProgram, "iColor"), 1, color);
	}
	// Setting Color RGBA
	void GraphicsOGL :: setColor(int R, int G, int B, int A) {

		// Set Color in OpenGl
		glColor4ub(R,G,B,A);

		// If No Shader Enabled, Quit
		if(curProgram == 0)
			return;

		float color[4];
		color[0] = R/255.;
		color[1] = G/255.;
		color[2] = B/255.;
		color[3] = A/255.;

		// Pass Color to Shader as Array
		glUniform4fv(glGetUniformLocation(curProgram, "iColor"), 1, color);
	}

	// Draw Point
	void GraphicsOGL :: drawPoint(float x, float y) {
		float depth = 0;
	
		// Create Point Primitive at Point (x,y)
		glBegin(GL_POINTS);
			glVertex3f(x, y, depth);
		glEnd();
	}

	// Draw 2D Line
	void GraphicsOGL :: drawLine(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		// Create Line Primitive from (x1,y1) to (x2,y2)
		glBegin(GL_LINES);
			glVertex3f(x1, y1, depth);
			glVertex3f(x2, y2, depth);
		glEnd();
	}

	// Draw Rectangle Outline
	void GraphicsOGL :: drawRect(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		// Draw Outlined Rectangle
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
	// Draw Filled Rectangle
	void GraphicsOGL :: fillRect(float x1, float y1, float x2, float y2) {
		float depth = 0;
	
		// Create Rectangle Primitive
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

	// Draw Circle Outline
	void GraphicsOGL :: drawCircle(float x, float y, float r, int vertNum) {
		float depth = 0, dir, xN, yN;
	
		// Loop through Points in Circle
		glBegin(GL_LINE_LOOP);
			for(float i = 0; i < vertNum; i++) {
				dir = i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				// Create Current Point
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}
	// Draw Filled Circle
	void GraphicsOGL :: fillCircle(float x, float y, float r, int vertNum) {
		float depth = 0, dir, xN, yN;
	
		// Begin Circle Primitive
		glBegin(GL_TRIANGLE_FAN);
			// Create Center Point, Center of Fan
			glTexCoord2f(.5,.5);
				glVertex3f(x, y, depth);
			// Go around Outside Pts
			for(float i = 0; i < vertNum+1; i++) {
				dir = i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	// Draw Polygon Outline
	void GraphicsOGL :: drawPolygon(float x, float y, float r, int vertNum, float angle) {
		float depth = 0, dir, xN, yN;
	
		// Create Polygon Primitive
		glBegin(GL_LINE_LOOP);
			for(float i = 0; i < vertNum; i++) {
				dir = angle + i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				// Create Points along Outline
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}
	// Draw Filled Polygon
	void GraphicsOGL :: fillPolygon(float x, float y, float r, int vertNum, float angle) {
		float depth = 0, dir, xN, yN;
	
		// Start Primitive
		glBegin(GL_TRIANGLE_FAN);
			// Create Center Point, Center of Fan
			glTexCoord2f(.5,.5);
				glVertex3f(x, y, depth);
			// Loop through Outside Points
			for(float i = 0; i < vertNum+1; i++) {
				dir = angle + i/vertNum*360;
				xN = calcLenX(1,dir);
				yN = -calcLenY(1,dir);
	
				glTexCoord2f(xN,yN);
					glVertex3f(x + r*xN, y + r*yN, depth);
			}
		glEnd();
	}

	// Draw Textured Rectangle
	void GraphicsOGL :: drawTexture(float x, float y, Texture* tex) {
		drawTextureScaled(x, y, 1, 1, tex);
	}
	// Draw Textured Rectangle Scaled
	void GraphicsOGL :: drawTextureScaled(float x, float y, float xS, float yS, Texture* tex) {

		// If Texture Doesn't Exist, Print Error and Quit
		if(tex == NULL) {
			cout << "Attempted to draw NULL texture." << endl;
			return;
		}

		// Otherwise, Enable Texture
		glEnable(GL_TEXTURE_2D);
		tex->bind();

		float depth = 0, w, h;
		w = xS*tex->getWidth();
		h = yS*tex->getHeight();

		// Create Textured Primitive
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

		// Unbind Texture
		glDisable(GL_TEXTURE_2D);
		tex->unbind();
	}


//3D DRAWING

	// TRANSFORMATIONS
		// Transform Model Translation
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
		// Transform Scale Uniformly
		void GraphicsOGL :: transformScale(float s) {
			transformScale(s, s, s);
		}
		// Transform Scale Nonuniformly
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
		// Rotate Model around X Axis
		void GraphicsOGL :: transformRotationX(float angle) {
			// OpenGL Rotate Function
			glRotatef(angle, 1, 0, 0);

			// Create Rotation Matrix
			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(1, 0, 0, 0,
				0, co, -si, 0,
				0, si, co, 0,
				0, 0, 0, 1);

			// Apply Rotation Matrix to Model Matrix
			modelMat *= rot;
		}
		// Rotate Matrix around Y Axis
		void GraphicsOGL :: transformRotationY(float angle) {
			// OpenGL Rotation
			glRotatef(angle, 0, 1, 0);

			// Create Rotation Matrix
			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(co, 0, si, 0,
				0, 1, 0, 0,
				-si, 0, co, 0,
				0, 0, 0, 1);

			// Apply Rotation Matrix to Model Matrix
			modelMat *= rot;
		}
		// Rotate Matrix around Z Axis
		void GraphicsOGL :: transformRotationZ(float angle) {
			// OpenGL Rotation
			glRotatef(angle, 0, 0, 1);

			// Create Rotation Matrix
			angle *= -1./180*3.14159;
			float co = cos(angle), si = sin(angle);

			mat4 rot(co, -si, 0, 0,
				si, co, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);

			// Apply Rotation Matrix to Model Matrix
			modelMat *= rot;
		}
		// Clear Transformations
		void GraphicsOGL :: transformClear() {
			// OpenGL Clear
			glLoadIdentity();
			// Set Identity in Model Matrix
			modelMat.setIdentity();
		}

	// PRIMITIVES
		// Draw 3D Sphere w/o Texture
		void GraphicsOGL :: draw3DSphere(float x, float y, float z, float r, int numPts) {
			draw3DSphere(x,y,z,r,numPts, NULL);
		}
		// Draw 3D Sphere w/ Texture
		void GraphicsOGL :: draw3DSphere(float x, float y, float z, float r, int numPts, Texture* tex) {
			float z1, z2, xN1,yN1, xN2,yN2, zDir1, zDir2, xyN1,xyN2, zN1, zN2, dir;

			// If Texture not Null, Enable
			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}

			// Create Textured Strips that run Horizontally
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

					// Current Point
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

					//Next Point
					glTexCoord2f((j+1)/numPts,i/numPts);
					glNormal3f(xN1,yN1,zN1);
						glVertex3f(x+xN1*r, y+yN1*r, z+zN1*r);
					glTexCoord2f((j+1)/numPts,(i+1)/numPts);
					glNormal3f(xN2,yN2,zN2);
						glVertex3f(x+xN2*r, y+yN2*r, z+zN2*r);
				}

				glEnd();
			}

			// If Texture Exists, Unbind
			if(tex != NULL) {
				glDisable(GL_TEXTURE_2D);
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		// Draw 3D Wall, Untextured
		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2) {
			draw3DWall(x1,y1,z1,x2,y2,z2,NULL);
		}
		// Draw 3D Wall, w/o Repeat
		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex) {
			draw3DWall(x1,y1,z1,x2,y2,z2,tex,1,1);
		}
		// Draw 3D Wall
		void GraphicsOGL :: draw3DWall(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex, float xRepeat, float yRepeat) {

			// If Texture Exists, Bind
			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}
			
			// Fix Alpha for Texturing
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			// Create Primitive
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

			// If Texture Exists, Unbind
			if(tex != NULL) {
				tex->unbind();
				glDisable(GL_TEXTURE_2D);
				setShaderInt("textureBound",0);
			}
		}

		// Draw 3D Floor, Untextured
		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z) {
			draw3DFloor(x1,y1,x2,y2,z,NULL);
		}
		// Draw 3D Floor w/o Repeat
		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z, Texture* tex) {
			draw3DFloor(x1,y1,x2,y2,z,tex,1,1);
		}
		// Draw 3D Floor
		void GraphicsOGL :: draw3DFloor(float x1, float y1, float x2, float y2, float z, Texture* tex, float xRepeat, float yRepeat) {

			// If Texture Exists, Bind
			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}
			
			// Fix Alpha for Texture
			glAlphaFunc(GL_GREATER, 0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
			// Create Primitive
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

			// Unbind Texture if Exists
			if(tex != NULL) {
				tex->unbind();
				glDisable(GL_TEXTURE_2D);
				setShaderInt("textureBound",0);
			}
		}

		// Draw 3D Line
		void GraphicsOGL :: draw3DLine(float x1, float y1, float z1, float x2, float y2, float z2) {
			// Create Line Primitive from (x1,y1,z1) to (x2,y2,z2)
			glBegin(GL_LINES);
				glVertex3f(x1, y1, z1);
				glVertex3f(x2, y2, z2);
			glEnd();
		}

		// Draw 3D Block, Untextured
		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2) {
			draw3DBlock(x1,y1,z1,x2,y2,z2,NULL);
		}
		// Draw 3D Block, w/o Repeat
		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2, Texture* tex) {
			draw3DBlock(x1,y1,z1,x2,y2,z2,tex,tex);
		}
		// Draw 3D Block
		void GraphicsOGL :: draw3DBlock(float x1, float y1, float z1, float x2, float y2, float z2, Texture* texWall, Texture* texFloor) {
			
			// Draw Walls
			draw3DWall(x1,y1,z1,x1,y2,z2,texWall);
			draw3DWall(x2,y1,z1,x2,y2,z2,texWall);
			draw3DWall(x1,y1,z1,x2,y1,z2,texWall);
			draw3DWall(x1,y2,z1,x2,y2,z2,texWall);
			
			// Draw Floors
			draw3DFloor(x1,y1,x1,y2,z1,texFloor);
			draw3DFloor(x1,y1,x1,y2,z2,texFloor);
		}

		// Draw 3D Circle, Untextured
		void GraphicsOGL :: draw3DCircle(float x, float y, float z, float rad, int sideNum) {
			draw3DPrism(x,y,z,rad,0,sideNum,NULL);
		}
		// Draw 3D Circle, Textured
		void GraphicsOGL :: draw3DCircle(float x, float y, float z, float rad, int sideNum, Texture* tex) {
			draw3DPrism(x,y,z,rad,0,sideNum,tex);
		}

		// Draw 3D Cone, Untextured
		void GraphicsOGL :: draw3DCone(float x, float y, float z, float rad, float h, int sideNum) {
			draw3DCone(x,y,z,rad,h,sideNum,NULL);
		}
		// Draw 3D Cone, Textured
		void GraphicsOGL :: draw3DCone(float x, float y, float z, float rad, float h, int sideNum, Texture* tex) {
			draw3DFrustem(x,y,z,rad,0,h,sideNum,tex);
		}

		// Drawing 3D Frustem, Untextured
		void GraphicsOGL :: draw3DFrustem(float x, float y, float z, float radBot, float radTop, float h, int sideNum) {
			draw3DFrustem(x,y,z,radBot,radTop,h,sideNum,NULL);
		}
		// Drawing 3D Frustem, Textured
		void GraphicsOGL :: draw3DFrustem(float x, float y, float z, float radBot, float radTop, float h, int sideNum, Texture* tex) {
			float ang = 45, dir, xN, yN;

			// If Texture Exists, Bind
			if(tex != NULL) {
				glEnable(GL_TEXTURE_2D);
				tex->bind();
				setShaderInt("textureBound",1);
			}

			// Draw Top of Frustem Primitive
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
				// Draw Bottom of Frustem Primitive
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

				// Draw Side Faces of Frustem Primitive
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

			// If Texture Exists, Unbind
			if(tex != NULL) {
				glDisable(GL_TEXTURE_2D);
				tex->unbind();
				setShaderInt("textureBound",0);
			}
		}

		// Drawing 3D Prism, Untextured
		void GraphicsOGL :: draw3DPrism(float x, float y, float z, float rad, float h, int sideNum) {
			draw3DPrism(x,y,z,rad,h,sideNum,NULL);
		}
		// Drawing 3D Prism, Textured
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
	// Draw Healthbar, Autoscaling
	void GraphicsOGL :: drawHealth(float dX, float dY, float amt, float maxAmt) {
		float s;
		if(maxAmt <= 20)
			s = 1;
		else
			s = .5;
		drawHealth(dX,dY,s,amt,maxAmt);
	}
	// Draw Healthbar
	void GraphicsOGL :: drawHealth(float dX, float dY, float scale, float amt, float maxAmt) {
		// Fix for Negative Health
		if(amt < 0)
			amt = 0;

		// Get Heart Textures
		Texture *h0, *h1, *h2, *h3, *h4, *cur;
		h0 = TextureController::getTexture("Heart0");
		h1 = TextureController::getTexture("Heart1");
		h2 = TextureController::getTexture("Heart2");
		h3 = TextureController::getTexture("Heart3");
		h4 = TextureController::getTexture("Heart4");
		
		// Loop through Hearts
		float startX = dX;
		float s = 16;
		int lineSkip = 10/scale;
		for(int i = 0; i < maxAmt; i++) {

			// Jump to Next Line
			if(i != 0 && i % lineSkip == 0) {
				dX = startX;
				dY += scale*(s+1);
			}

			// Get Current Texture
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

			// Draw Heart
			drawTextureScaled(dX,dY,scale*h0->getWidth()/s,scale*h0->getHeight()/s,cur);
			// Move to Right
			dX += scale*(s+1);
		}
	}

//SHADERS

	// Passing Float to Shader
	void GraphicsOGL :: setShaderVariable(string varName, float value) {
		glUniform1f(glGetUniformLocation(curProgram, varName.c_str()), value);
	}
	// Passing Int to Shader
	void GraphicsOGL :: setShaderInt(string varName, int value) {
		glUniform1i(glGetUniformLocation(curProgram, varName.c_str()), value);
	}
	//Passing 3x1 Vector to Shader
	void GraphicsOGL :: setShaderVec3(string varName, float array[3]) {
		glUniform3fv(glGetUniformLocation(curProgram, varName.c_str()), 1, array);
	}
	// Passing 4x4 Matrix to Shader
	void GraphicsOGL :: setShaderMat4(string varName, mat4& matrix) {
		float mmFloats[16];
		// Get Matrix as 1D Array
		matrix.getArray(mmFloats);

		// Pass 1D Array to Shader
		glUniformMatrix4fv(glGetUniformLocation(curProgram, varName.c_str()), 1, GL_FALSE, mmFloats);
	}
	// Passing View Matrix to Shader
	void GraphicsOGL :: passViewMatrix() {
		float camPos[3], camNorm[3];
		glCamera->getPosition(camPos);
		glCamera->getNormal(camNorm);

		// Get Camera Position, Looking Normal, and Up Normal
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
		
		// Forward Direction
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

		// Create View Matrix
		mat4 viewMat(sX,uX,-lX,-eyeX,sY,uY,-lY,-eyeY,sZ,uZ,-lZ,-eyeZ,0,0,0,1);
		// Transpose View Matrix
		viewMat = viewMat.transpose();

		// Pass View Matrix
		setShaderMat4("viewMatrix", viewMat);
	}
	// Pass Transformation Matrix for Models to Shader
	void GraphicsOGL :: passModelMatrix() {
		setShaderMat4("modelMatrix", modelMat);
	}
	// Update Values to be Passed to Shaders
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

			// Loop through Characters
			for(int i = 0; i < Character::characterList.size(); i++) {
				Character* c = Character::characterList[i];
				curX = c->getX();
				curY = c->getY();

				// Only Worry about Character if Onscreen
				if(!c->getOnScreen())
					continue;

				// Add Shadow Position
				shadowLocations[numShadows*3+0] = curX;
				shadowLocations[numShadows*3+1] = curY;
				shadowLocations[numShadows*3+2] = 6;				
				numShadows++;

				// Add Light if Dying
				float f = c->getDestroyFraction();
				if(f != -1) {
					float flicker = .2*sqr(f)*(rnd()-.5);

					// Set Position
					lightLocations[numLights*3+0] = curX + 4*f*(rnd()-.5);
					lightLocations[numLights*3+1] = curY + 4*f*(rnd()-.5);
					lightLocations[numLights*3+2] = c->getZ() + 4*f*(rnd()-.5);
					// Set Color to Red
					lightColors[numLights*4+0] = 1;
					lightColors[numLights*4+1] = 0;
					lightColors[numLights*4+2] = 0;
					// Set Alpha so it Increases in Intensity
					lightColors[numLights*4+3] = f+flicker;
					// Set Radius so it Increases in Size
					lightRadii[numLights] = 25*(sqr(f)+flicker);
					numLights++;
				}
			}

			// Loop through Trees
			for(int i = 0; i < Tree::treeList.size(); i++) {
				Tree* t = Tree::treeList[i];

				// If Tree Doesn't Have Shadow (is a Bush) or Isn't Onscreen, Ignore
				if(!t->getHasShadow() || !t->getOnScreen())
					continue;

				curX = t->getX();
				curY = t->getY();
				curRad = 32*t->getSize();
				
				// Add XY Position, Radius
				shadowLocations[numShadows*3+0] = curX;
				shadowLocations[numShadows*3+1] = curY;
				shadowLocations[numShadows*3+2] = curRad;				
				numShadows++;
			}


		// SET UP LIGHT LIST
		////////////////////////////////////////////////////
		for(int i = 0; i < Lamp::lampList.size(); i++) {
			Lamp* l = Lamp::lampList[i];
			curR = l->getLightR();
			curG = l->getLightG();
			curB = l->getLightB();
			curA = l->getLightA();
			curRad = l->getLightRadius();

			// Light Coordinates
			lightLocations[numLights*3+0] = l->getLightX();
			lightLocations[numLights*3+1] = l->getLightY();
			lightLocations[numLights*3+2] = l->getLightZ();
			// Light Color
			lightColors[numLights*4+0] = curR;
			lightColors[numLights*4+1] = curG;
			lightColors[numLights*4+2] = curB;
			lightColors[numLights*4+3] = curA;
			// Light Radius
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
	// Function for Passing Path to Shader
	void GraphicsOGL :: passShaderPath() {
		glUniform3fv(glGetUniformLocation(curProgram, "pathPts"), 100, dp->pts);
		glUniform1i(glGetUniformLocation(curProgram, "pathPtNum"), dp->numPts);
	}

	// Disabling Shaders
	void GraphicsOGL :: disableShaders() {
		glUseProgram(0);
	}

	// Enabling a Shader w/ Name
	void GraphicsOGL :: enableShader(string name) {
	
		// Get Shader Program
		curShader = shaderController->getShader(name);

		// Get Noise Texture
		Texture* noiseTex = TextureController::getTexture("Noise");

		// Set Current Shader Program
		curProgram = curShader->getProgram();

		// Enable Current Shader
		glUseProgram(curProgram);

		// Pass Screen Resolution and Time Value (Used in Animations) to Shader
		glUniform2fv(glGetUniformLocation(curProgram, "iResolution"), 1, resolution);			
    		glUniform1f(glGetUniformLocation(curProgram, "iGlobalTime"), globalTime/50.);      
		glUniform1f(glGetUniformLocation(curProgram, "iRadius"), 0);

		// Get Camera Position and Direction
		float camNormal[3], camPos[3], sCamPos[3], camDir[3];
		glCamera->getNormal(camNormal);
		glCamera->getPosition(camPos);
		glCamera->getShaderPosition(sCamPos);
		glCamera->getDirection(camDir);

		// Pass Camera Position and Direction to Shader
		glUniform3fv(glGetUniformLocation(curProgram, "camNormal"), 1, camNormal);		
		glUniform3fv(glGetUniformLocation(curProgram, "rCamPos"), 1, camPos);
		glUniform3fv(glGetUniformLocation(curProgram, "iCamPos"), 1, sCamPos);
		glUniform3fv(glGetUniformLocation(curProgram, "iCamDir"), 1, camDir);  

		// Pass Sea Level to Shader
		glUniform1f(glGetUniformLocation(curProgram, "seaLevel"), terrain->getSeaLevel());  

		// Pass Texture(s) to Shader
		glUniform1i(glGetUniformLocation(curProgram, "Texture0"), 0);
		glUniform1i(glGetUniformLocation(curProgram, "Texture1"), 1);
		glUniform1i(glGetUniformLocation(curProgram, "Texture2"), 3);
		glUniform1i(glGetUniformLocation(curProgram, "noiseTex"), 2);
	}

	// Pass Texture Size to Shader
	void GraphicsOGL :: setCurrentTextureSize(int w, int h) {
	
		// If Not in Shader, Ignore
		if(curProgram == 0)
			return;

		float si[2];
		si[0] = w;
		si[1] = h;

		// Pass Texture Size as 2x1 Vector
		glUniform2fv(glGetUniformLocation(curProgram, "iSize"), 1, si);				
	}

//TEXT DRAWING
	// Set Current Drawing Font
	void GraphicsOGL :: setFont(string name) {
		curFont = fontController->getFont(name);
	}
	// Draw Single Character
	float GraphicsOGL :: drawChar(float x, float y, char c) {
		return drawCharScaled(x, y, 1, 1, c);
	}
	// Draw Character Scaled
	float GraphicsOGL :: drawCharScaled(float x, float y, float xS, float yS, char c) {
	
		// Get Texture
		Texture* t = curFont->getChar(c);
		
		// If Texture Doesn't Exist, Ignore
		if(t == NULL) {
			cout << "Attempted to draw a character not present in the font." << endl;
			return 0;
		}

		// For Letters w/ Tails, Draw Lower
		if(c == 'y' || c == 'g' || c == 'j' || c == 'p' || c == 'q')
			y += .25*t->getHeight()*yS;

		// Draw Texture
		drawTextureScaled(x, y, xS, yS, t);
		
		// Return Width of Character so Next Character is to Right
		return t->getWidth()*xS;
	}
	// Draw String Unscaled
	void GraphicsOGL :: drawString(float x, float y, string str) {
		drawStringScaled(x,y,1,1,str);
	}
	// Draw Scaled String
	void GraphicsOGL :: drawStringScaled(float x, float y, float xS, float yS, string str) {
		int len = str.length();
		char c;
		float s = curFont->getWidth(), e = -1;
		float dX = x, dY = y;

		// Loop through All Text, Draw
		for(int i = 0; i < len; i++) {
			c = str[i];

			// On Newline, Jump to Next Line and Move back Left
			if(c == '\n') { 
				dY += s*yS + e*yS;
				dX = x;
			}
			// On Space, Jump Right
			else if(c == ' ')
				dX += s*xS + e*xS;
			// For Lowercase, Shrink Text Slightly Vertically and Move Right
			else if(islower(c))
				dX += drawCharScaled(dX,dY + (s*yS*.25), xS,yS*.75, c) + e*xS;
			// For Uppercase, Draw Normally and Move Right
			else
				dX += drawCharScaled(dX,dY, xS, yS, c) + e*xS;
		}
	}

//Graphics Modes
	// 2D Drawing
	void GraphicsOGL :: setOrtho() {

		// Set Orthographic Projection
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1000, 1000);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity();
		
		// Diable Lighting and Depth
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH);
	}
	// 3D Drawing
	void GraphicsOGL :: setPerspective() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glCamera->setProjection(this);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// Enable Depth
		glEnable(GL_DEPTH);
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
	// Get Input Controller
	InputController* GraphicsOGL :: getInputController() {
		return inputController;
	}
	// Getting Heightmap
	Heightmap* GraphicsOGL :: getHeightmap() {
		return terrain->getHeightmap();
	}
	// Get Text Controller
	TextController* GraphicsOGL :: getTextController() {
		return tc;
	}
	// Get Sound Controller
	SoundController* GraphicsOGL :: getSoundController() {
		return sc;
	}
