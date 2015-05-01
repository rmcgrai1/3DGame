// GraphicsOGL.h
// Ryan McGrail

#ifndef GRAPHICSOGL_H
#define GRAPHICSOGL_H

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "Font.h"
#include "../IO/InputController.h"
#include "ShaderController.h"
#include "TextureController.h"
#include "FontController.h"
#include "Camera.h"
#include "../Environment/Heightmap.h"
#include "../Environment/Terrain.h"
#include "../Characters/Player.h"
#include "../menus/menu.h"
#include "../Environment/Shapes/PieceController.h"
#include "../Text/TextController.h"
#include "../Sound/SoundController.h"
#include "models/Model.h"
#include "../Functions/mat4.h"


class Camera;
class Heightmap;
class TextController;
class SoundController;
class GraphicsOGL {
	public:
		GraphicsOGL(int, char* []);
		~GraphicsOGL();


		void idle();
		void display();

		void logMessage(string);

		void setDepthTest(bool);																	// Set Depth Testing
		void setCulling(bool);																		// Set Culling
		
		Player* getPlayer();																		// Get Player
		Menu* getMenu();																			// Get Menu
		PieceController* getPieceController();														// Get Piece Controller
		Camera* getCamera();																		// Get Camera
		InputController* getInputController();														// Get Input Controller
		TextController* getTextController();														// Get Text Controller
		SoundController* getSoundController();														// Get Sound Controller

		// Slow PC??
			int isPCSlow();																			// Checking for if PC is Slow (Low FPS)

		//ACCESSOR
			int getScreenWidth();																	// Get Width of Screen
			int getScreenHeight();																	// Get Height of Screen
			
		//CAMERA
			float getCamDir();																		// Get Camera Direction
			void setProjectionPrep(float,float,float,float,float,float);							// Prepare Camera Projection
		
		// DRAWING
			void setColor(int,int,int);																// Set RGB
			void setColor(int,int,int,int);															// Set RGBA

		//2D DRAWING
			// 2D PRIMITIVES
				void drawPoint(float,float);														// Draw Point
				void drawLine(float,float,float,float);												// Draw Line
				void drawRect(float,float,float,float);												// Draw Rectangle Outline
				void fillRect(float,float,float,float);												// Fill Rectangle
				void drawCircle(float,float,float,int);												// Draw Circle Outline
				void fillCircle(float,float,float,int);												// Fill Circle
				void drawPolygon(float,float,float,int,float);										// Draw Polygon Outline
				void fillPolygon(float,float,float,int,float);										// Fill Polygon

			// TEXTURES
				void drawTexture(float, float, Texture*);											// Draw Texture
				void drawTextureScaled(float, float, float, float, Texture*);						// Draw Scaled Texture

			// TEXT
				float drawChar(float, float, char);													// Draw Character
				float drawCharScaled(float, float, float, float, char);								// Draw Scaled Character
				void drawString(float, float, string);												// Draw String
				void drawStringScaled(float, float, float, float, string);							// Draw Scaled String

				void drawHealth(float,float,float,float);											// Draw Healthbar
				void drawHealth(float,float,float,float,float);


		// 3D DRAWING
			// 3D TRANSFORMATIONS
				void transformTranslation(float, float, float);										// Transform Translation for 3D Models
				void transformScale(float);															// Transform Scale for 3D Models
				void transformScale(float, float, float);											
				void transformRotationX(float);														// Transform Rotation around X Axis for 3D Models
				void transformRotationY(float);														// Transform Rotation around Y Axis for 3D Models
				void transformRotationZ(float);														// Transform Rotation around Z Axis for 3D Models
				void transformClear();																// Clear Transformation for 3D Models


			//3D PRIMTITIVES
				void draw3DSphere(float,float,float,float,int);										// Draw 3D Sphere
				void draw3DSphere(float,float,float,float,int,Texture*);

				void draw3DWall(float,float,float,float,float,float);								// Draw 3D Wall
				void draw3DWall(float,float,float,float,float,float, Texture*);
				void draw3DWall(float,float,float,float,float,float, Texture*, float, float);

				void draw3DFloor(float,float,float,float,float);									// Draw 3D Floor
				void draw3DFloor(float,float,float,float,float, Texture*);
				void draw3DFloor(float,float,float,float,float, Texture*, float, float);

				void draw3DBlock(float,float,float,float,float,float);								// Draw 3D Block
				void draw3DBlock(float,float,float,float,float,float, Texture*);
				void draw3DBlock(float,float,float,float,float,float, Texture*, Texture*);

				void draw3DCircle(float,float,float,float,int);										// Draw Flat 3D Circle
				void draw3DCircle(float,float,float,float,int, Texture*);

				void draw3DCone(float,float,float,float,float,int);									// Draw 3D Cone
				void draw3DCone(float,float,float,float,float,int, Texture*);

				void draw3DFrustem(float,float,float,float,float,float,int);						// Draw 3D Frustem
				void draw3DFrustem(float,float,float,float,float,float,int, Texture*);				

				void draw3DPrism(float,float,float,float,float,int);								// Draw 3D Prism
				void draw3DPrism(float,float,float,float,float,int, Texture*);

				void draw3DLine(float,float,float,float,float,float);								// Draw 3D Line
			//3D MODEL
			void draw3DModel(Model *);																// Draw .obj File

				
		//SHADERS
			void setShaderVariable(string, float);													// Pass Float to Shader							
			void setShaderInt(string, int);															// Pass Int to Shader
			void setShaderMat4(string, mat4&);														// Pass 4x4 Matrix to Shader
			void setShaderVec3(string, float[3]);													// Pass 3x1 Vector to Shader
			void passViewMatrix();																	// Pass View Matrix to Shader
			void passModelMatrix();																	// Pass Model Matrix to Shader
			void passShaderUpdate();																// Update Values to Pass to Shader
			void passShaderShadows();																// Pass Shadows to Shader
			void passShaderPath();																	// Pass Path to Shader
			void passShaderLights();																// Pass Lights to Shader
			void disableShaders();																	// Disable Shader
			void enableShader(GLuint);																// Enable Shader w/ Program
			void enableShader(string);																// Enable Shader w/ String
			void enableWaterShader();																// Enable Water Shader
			void enableSkyShader();																	// Enable Sky Shader
			void setCurrentTextureSize(int,int);													// Pass Texture Size to Shader

		//FONT
			void setFont(string);																	// Set Current Font

		//HEIGHTMAP
			Heightmap* getHeightmap();																// Get Heightmap

		//PROJECTION
			void setOrtho();																		// Enable 2D Mode for Drawing
			void setPerspective();																	// Enable 3D Mode for Drawing

	private:
		void initialize3D(int, char* []);															// Initialize 3D Elements

		int SCREEN_WIDTH;																			// Width of Screen
		int SCREEN_HEIGHT;																			// Height of Screen

			Player* myPlayer;																		// Main Player
			Menu* myMenu;																			// Player
			PieceController* AllStructures;															// Array of PieceController Structures

		//FPS Variables
			unsigned long fpsStart, fpsEnd;															// Times for FPS (Updating)
			unsigned long drawStart, drawEnd;														// Times for FPS (Drawing)
			int fps;																				// Current FPS
			float avgFPS;																			// Average FPS (for isPCSlow())

		//Heightmap Variables
			Terrain* terrain;																		// Terrain
			InputController* inputController;														// Input Controller
			ShaderController* shaderController;														// Shader Controller
			FontController* fontController;															// Font Controller
			SoundController* sc;																	// Sound Controller

		//Shader Variables
			Shader* curShader;																		// Current Shader
			GLuint curProgram;																		// Current Shader Program
			float* resolution;																		// Resolution of Screen for Shaders
			float globalTime;																		// Float for Time-Based Shaders

		//Font Variables
			Font2D* curFont;																		// Currently-Used Font

		Camera* glCamera;																			// Camera
};

#endif
