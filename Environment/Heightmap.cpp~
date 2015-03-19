// Heightmap.cpp


#include <iostream>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TextureController.h"
#include "../Primitives/Drawable.h"
#include <cmath>
#include "Heightmap.h"
#include "../Graphics/Texture.h"
#include "../Functions/Math2D.h"
#include "../Global.h"
#include "../Graphics/Image.h"
using namespace std;

Heightmap :: Heightmap(float xS, float yS, float resolution) {
	xSize = xS;
	ySize = yS;

	scale = 1/resolution;

	xNum = xS*resolution; yNum = yS*resolution;

	heightGrid = new float*[yNum];

	for(int i = 0; i < yNum; i++) {
		heightGrid[i] = new float[xNum];

		for(int j = 0; j < xNum; j++)
			setHeight(i,j,i*j);
	}

	texGrass = NULL;
	texSand = NULL;

	generateNormals();
}

Heightmap :: Heightmap(TextureController* tc, float xS, float yS, string fileName) {
	xSize = xS;
	ySize = yS;


	hmImg = new Image(fileName);

	// Determine XY Scale
	scale = xS/hmImg->getWidth();

	// Set # of Points
	xNum = hmImg->getWidth();
	yNum = hmImg->getHeight();


	// Create Array
	heightGrid = new float*[yNum];


	// Set Heights
	for(int i = 0; i < yNum; i++) {
		heightGrid[i] = new float[xNum];

		// Set Height to Value of Current Pixel
		for(int j = 0; j < xNum; j++)
			setHeight(i,j,hmImg->getValue(j,i));
	}

	texGrass = tc->getTexture("Grass");
	texSand = tc->getTexture("Sand");


	generateNormals();
}

//		Heightmap(float, float, int**);
//		Heightmap(float, float, float**);

float Heightmap :: getHeightIJ(int i, int j) {
	if(i < 0 || j < 0 || i >= yNum || j >= xNum)
		return -1;
	else
		return heightGrid[i][j];
}

float Heightmap :: getHeightXY(float x, float y) {

	//if(x <= 0 || y <= 0 || x > xSize-1 || y > ySize-1)
	//	return -1;
	

	float h1, h2, h3, h4;
	int jC, jF, iC, iF;


	//Get (i,j) Coordinates of (x,y) point
	float jP, iP;
	jP = x/scale;
	iP = y/scale;

	//Get (i,j) Coordinates of Corners
	jC = ceil(jP);
	jF = jC-1;
	iC = ceil(iP);
	iF = iC-1;

	//Get Distance Into Square from Left Corner
	float xP, yP;
	xP = (jP - jF);
	yP = (iP - iF);	


	// Get Heights at Four Corners
	h1 = getHeightIJ(iF,jF);
	h2 = getHeightIJ(iF,jC);
	h3 = getHeightIJ(iC,jF);
	h4 = getHeightIJ(iC,jC);


	// Return Weighted Average of Points
	return (1-xP)*(1-yP)*h1 + (xP)*(1-yP)*h2 + (1-xP)*(yP)*h3 + (xP)*(yP)*h4;
}


void Heightmap :: getNormal(float x, float y, float vec[3]) {
	float h1, h2, h3, h4;
	int jC, jF, iC, iF;

	//Get (i,j) Coordinates of (x,y) point
	float jP, iP;
	jP = x/scale;
	iP = y/scale;

	//Get (i,j) Coordinates of Corners
	jC = ceil(jP);
	jF = jC-1;
	iC = ceil(iP);
	iF = iC-1;

	//Get Distance Into Square from Left Corner
	float xP, yP;
	xP = (jP - jF);
	yP = (iP - iF);	


	// Get Heights at Four Corners
	h1 = getHeightIJ(iF,jF);
	h2 = getHeightIJ(iF,jC);
	h3 = getHeightIJ(iC,jF);
	h4 = getHeightIJ(iC,jC);


	
	//	A --- C
	//	|     |
	//	|     |
	//	B ----D

	

	float Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz;
	// Get Coords of Three Points
		if(calcPtDis(jP,iP,jF,iF) < calcPtDis(jP,iP,jC,iC)) {		
			Ax = jF*scale;	Ay = iF*scale;	Az = h1;
			Bx = jF*scale;	By = iC*scale;	Bz = h3;
			Cx = jC*scale;	Cy = iF*scale;	Cz = h2;
		}
		else {
			Ax = jC*scale;	Ay = iF*scale;	Az = h2;
			Bx = jF*scale;	By = iC*scale;	Bz = h3;
			Cx = jC*scale;	Cy = iC*scale;	Cz = h4;
		}

	// (B-A) x (C-A)
		float BAx, BAy, BAz, CAx, CAy, CAz;
		BAx = Bx-Ax;	CAx = Cx-Ax;
		BAy = By-Ay;	CAy = Cy-Ay;
		BAz = Bz-Az;	CAz = Cz-Az;

		float Dx, Dy, Dz;
		Dx = BAy*CAz - BAz*CAy;
		Dy = -(BAx*CAz - BAz*CAx);
		Dz = BAx*CAy - BAy*CAx;

	// Normalize
		float len = -sqrt(Dx*Dx + Dy*Dy + Dz*Dz);

		Dx /= len;	Dy /= len;	Dz /= len;

	// Set Values in Vector
		vec[0] = Dx;	vec[1] = Dy;	vec[2] = Dz;
}
//bool isFloor(float, float);

void Heightmap :: generateNormals() {
	float n1[3],n2[3],n3[3],n4[3];

	normGrid = new float**[yNum];

	float s = scale;

	for(int y = 0; y < yNum; y++) {
		normGrid[y] = new float*[xNum];

		for(int x = 0; x < xNum; x++) {
			normGrid[y][x] = new float[3];


			float dList[6] = {30,60,135,210,240,315};

			float nX=0,nY=0,nZ=0;
			for(int i = 0; i < 4; i++) {
				float curNorm[3];
				float d = dList[i], aX, aY;
				aX = calcLenX(3,d);
				aY = calcLenY(3,d);

				getNormal(x*scale+aX,y*scale+aY,curNorm);

				nX += curNorm[0];
				nY += curNorm[1];
				nZ += curNorm[2];
			}

			normGrid[y][x][0] = nX;
			normGrid[y][x][1] = nY;
			normGrid[y][x][2] = nZ;
			
		        // The ? : and ifs are necessary for the border cases.

			/*float sx = getHeightIJ(y, x<xNum-1 ? x+1 : x) - getHeightIJ(y, x > 0 ? x-1 : x);
			if (x == 0 || x == xNum-1)
			    sx *= 2;

			float sy = getHeightIJ(y<yNum-1 ? y+1 : y, x) - getHeightIJ(y > 0 ? y-1 : y,x);
			if (y == 0 || y == yNum -1)
			    sy *= 2;

			normGrid[y][x][0] = -sx*scale;
			normGrid[y][x][1] = sy*scale;
			normGrid[y][x][2] = 1;//*xzScale;*/

			float len = -sqrt(sqr(normGrid[y][x][0]) + sqr(normGrid[y][x][1]) + sqr(normGrid[y][x][2]));

			normGrid[y][x][0] /= len;
			normGrid[y][x][1] /= len;
			normGrid[y][x][2] /= len;
		}
	}
}


//bool isWall(float, float);
		
void Heightmap :: draw(GraphicsOGL* gl, float deltaTime) {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//GLfloat lightpos[] = {x, y, z, 1};
	GLfloat lightpos[] = {0,.6,-.8, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	gl->enableShader("Terrain");

	if(texGrass != NULL) {
		glEnable(GL_TEXTURE_2D);
	
		texGrass->bind(GL_TEXTURE0);
		texSand->bind(GL_TEXTURE1);
	}

	Drawable2 :: draw(gl, deltaTime);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	
	float num = xSize/32.;


	// Draw Heightmap as Triangle Strips

	for(int i = 0; i < yNum-1; i++) {

		glBegin(GL_TRIANGLE_STRIP);

		for(int j = 0; j < xNum; j++) {

			glTexCoord2f(num*1.*j/xNum, num*1.*i/yNum);
			glNormal3f(normGrid[i][j][0],normGrid[i][j][1],normGrid[i][j][2]);
				glVertex3f(j*scale, i*scale, getHeightIJ(i,j));
			glTexCoord2f(num*1.*j/xNum, num*1.*(i+1)/yNum);
			glNormal3f(normGrid[i+1][j][0],normGrid[i+1][j][1],normGrid[i+1][j][2]);
				glVertex3f(j*scale, (i+1)*scale, getHeightIJ(i+1,j));
		}

		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	

	gl->disableShaders();

	glDisable(GL_LIGHTING);
	// Added to make 2d images render correctly
	if(texGrass != NULL) {
		texGrass->unbind();
	}
	if(texSand != NULL) {
		texSand->unbind();
	}
	// Added to make 2d images render correctly
}

void Heightmap :: setHeight(int i, int j, float height) {
	heightGrid[i][j] = height;
}

//		void load(string);
