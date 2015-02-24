// Heightmap.cpp


#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "Heightmap.h"

Heightmap :: Heightmap(float xS, float yS, float resolution) {
	xSize = xS;
	ySize = yS;

	scale = 1/resolution;

	xNum = xS*resolution, yNum = yS*resolution;

	heightGrid = new float*[yNum];

	for(int i = 0; i < yNum; i++) {
		heightGrid[i] = new float[xNum];

		for(int j = 0; j < xNum; j++)
			setHeight(i,j,i*j);
	}
}

//		Heightmap(float, float, int**);
//		Heightmap(float, float, float**);

float Heightmap :: getHeight(int i, int j) {
	return heightGrid[i][j];
}
//void getNormal(float, float, float*);
//bool isFloor(float, float);
//bool isWall(float, float);
		
void Heightmap :: draw(GraphicsOGL* gl, float deltaTime) {
	Drawable :: draw(gl, deltaTime);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	for(float i = 0; i < yNum-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);

		for(float j = 0; j < xNum; j++) {
			glTexCoord2d(j/xNum,i/yNum);
				glVertex3d(j*scale, i*scale, getHeight(i,j));
			glTexCoord2d(j/xNum, (i+1)/yNum);
				glVertex3d(j*scale, (i+1)*scale, getHeight(i+1,j));
		}

		glEnd();
	}
}

void Heightmap :: setHeight(int i, int j, float height) {
	heightGrid[i][j] = height;
}

//		void load(string);
