// PineTree.cpp
// Ryan McGrail

#include "../Graphics/GraphicsOGL.h"
#include "../Functions/Math2D.h"
#include "PineTree.h"
#include "Tree.h"
#include "../Graphics/Texture.h"


// Constructor
PineTree :: PineTree(float nX, float nY, float size, float colR, float colG, float colB) : Tree(nX,nY,size) {

	// Set Color
	colRed = colR;
	colGreen = colG;
	colBlue = colB;

	hasShadow = true;
}

// Updating
void PineTree :: update(GraphicsOGL* gl, float deltaT) {
	Tree :: update(gl, deltaT);
}

// Drawing
void PineTree :: draw(GraphicsOGL* gl, float deltaT) {

	int fid = 3 + fidelity*4;
	float R = 20, G = 255, B = 50;
	float r = 15, dZ, h = 30, uR, uDZ, uH;


	// If Hurt, Shake
	float aX = 0, aY = 0;
	if(damageShakeTimer != -1) {
		aX = 2.*(rnd() - .5);
		aY = 2.*(rnd() - .5);
	}
	
	// Transform to Position
	gl->transformClear();
	gl->transformTranslation(x+aX,y+aY,z-5);
		gl->transformRotationZ(fallXYDir);
		gl->transformRotationY(fallZDir);
		gl->transformRotationZ(-fallXYDir);
	gl->transformScale(size);
	
	// If PC NOT Slow, Enable Bark Shader
	if(!gl->isPCSlow())
		gl->enableShader("pineBark");
	// Draw Bark w/ Prism and Cone
	gl->draw3DPrism(0,0,0,4,30, fid, barkTex);
	gl->draw3DCone(0,0,0,5,30, fid, barkTex);

	// If PC NOT Slow, Enable Branch Shader
	if(!gl->isPCSlow())
		gl->enableShader("pineBranch");

	// If Hurt, Turn Red
	if(damageShakeTimer != -1)
		gl->setColor(255*colRed, .2*255*colGreen, .2*255*colBlue);
	else
		gl->setColor(255*colRed, 255*colGreen, 255*colBlue);

	// Draw 3 Levels of Branches in Tree
	for (int i = 0; i < 3; i++) {
		r -= 2*i;
		dZ += 13+i;
		h -= 2*i;

		uR = r;
		uDZ = dZ;
		uH = h;
		// Drawing Multiple Branches at Current Height
		for (int j = 0; j < 1; j++) {
			uDZ += 3;
			
			gl->setShaderVariable("iDark", pow((3.-i)/3.,2.));

			float fR = sin((fallZDir/90.)*3.14159)*(-fallZVel*10);
			// Translate
			gl->transformTranslation(0,0,uDZ);
			gl->transformRotationZ(fallXYDir);
			gl->transformRotationY(fR);									// Rotate for Falling!!!
			gl->transformRotationZ(-fallXYDir);
				// Draw Branch as Cone
				gl->draw3DCone(0,0,0,uR,uH, fid, branchTex);
			// Untranslate
			gl->transformTranslation(0,0,-uDZ);
		}
	}

	// Reset OpenGL Drawing
	gl->setColor(255,255,255);
	gl->disableShaders();
	gl->transformClear();
}
