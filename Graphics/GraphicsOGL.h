// GraphicsOGL.h

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
#include "../Text/TextController.h"
#include "models/Model.h"

class Camera;
class Heightmap;
class TextController;
class GraphicsOGL {
	public:
		GraphicsOGL(int, char* []);
		~GraphicsOGL();


		bool gluInvertMatrix(const float [16], float [16]);
		void idle();
		void display();

		void logMessage(string);


		void setDepthTest(bool);
		void setCulling(bool);
		Player* getPlayer();
		Menu* getMenu();

		Camera* getCamera();
		InputController* getInputController();
		TextureController* getTextureController();
		TextController* getTextController();

		// Slow PC??
			int isPCSlow();

		//ACCESSOR
			int getScreenWidth();
			int getScreenHeight();
			

		//CAMERA
			float getCamDir();
			void setProjectionPrep(float,float,float,float,float,float);
		

		// DRAWING
			void setColor(int,int,int);
			void setColor(int,int,int,int);

		//2D DRAWING
			// 2D PRIMITIVES
				void drawPoint(float,float);
				void drawLine(float,float,float,float);
				void drawRect(float,float,float,float);
				void fillRect(float,float,float,float);
				void drawCircle(float,float,float,int);
				void fillCircle(float,float,float,int);
				void drawPolygon(float,float,float,int,float);
				void fillPolygon(float,float,float,int,float);

			// TEXTURES
				void drawTexture(float, float, Texture*);
				void drawTextureScaled(float, float, float, float, Texture*);

			// TEXT
				float drawChar(float, float, char);
				float drawCharScaled(float, float, float, float, char);
				void drawString(float, float, string);
				void drawStringScaled(float, float, float, float, string);

				void drawHealth(float,float,float,float);
				void drawHealth(float,float,float,float,float);


		// 3D DRAWING
			// 3D TRANSFORMATIONS
				void transformTranslation(float, float, float);
				void transformScale(float);
				void transformScale(float, float, float);
				void transformRotationX(float);
				void transformRotationY(float);
				void transformRotationZ(float);
				void transformClear();


			//3D PRIMTITIVES
				void draw3DSphere(float,float,float,float,int);
				void draw3DSphere(float,float,float,float,int,Texture*);

				void draw3DWall(float,float,float,float,float,float);
				void draw3DWall(float,float,float,float,float,float, Texture*);
				void draw3DWall(float,float,float,float,float,float, Texture*, float, float);

				void draw3DFloor(float,float,float,float,float);
				void draw3DFloor(float,float,float,float,float, Texture*);
				void draw3DFloor(float,float,float,float,float, Texture*, float, float);

				void draw3DBlock(float,float,float,float,float,float);
				void draw3DBlock(float,float,float,float,float,float, Texture*);
				void draw3DBlock(float,float,float,float,float,float, Texture*, Texture*);

				void draw3DCircle(float,float,float,float,int);
				void draw3DCircle(float,float,float,float,int, Texture*);

				void draw3DCone(float,float,float,float,float,int);
				void draw3DCone(float,float,float,float,float,int, Texture*);

				void draw3DFrustem(float,float,float,float,float,float,int);
				void draw3DFrustem(float,float,float,float,float,float,int, Texture*);

				void draw3DPrism(float,float,float,float,float,int);
				void draw3DPrism(float,float,float,float,float,int, Texture*);

				void draw3DLine(float,float,float,float,float,float);
			//3D MODEL
			void draw3DModel(Model *);

				
		//SHADERS
			void setShaderVariable(string, float);
			void passShaderShadows();
			void passShaderPath();
			void disableShaders();
			void enableShader(GLuint);
			void enableShader(string);
			void enableWaterShader();
			void enableSkyShader();
			void setCurrentTextureSize(int,int);

		//FONT
			void setFont(string);

		//HEIGHTMAP
			Heightmap* getHeightmap();

		//PROJECTION
			void setOrtho();
			void setPerspective();

		//TIME
			unsigned long getTime();

	private:
		void initialize3D(int, char* []);

		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;

			Player* myPlayer;
			Menu* myMenu;

		//FPS Variables
			unsigned long fpsStart, fpsEnd;
			unsigned long drawStart, drawEnd;
			int fps;
			float avgFPS;

		//Heightmap Variables
			Terrain* terrain;
			InputController* inputController;
			TextureController* textureController;
			ShaderController* shaderController;
			FontController* fontController;

		//Shader Variables
			Shader* curShader;
			GLuint curProgram;
			float* resolution;
			float globalTime;

		//Font Variables
			Font2D* curFont;

		Camera* glCamera;
};

#endif
