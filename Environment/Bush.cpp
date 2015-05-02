// Bush.cpp
// Ryan McGrail

#include "../Graphics/GraphicsOGL.h"
#include "Bush.h"
#include "../Functions/Math2D.h"
#include "Tree.h"
#include "../Graphics/Texture.h"


// Constructor
Bush :: Bush(float nX, float nY, float size, float colR, float colG, float colB) : Tree(nX,nY,size) {

	// Setting Color
	colRed = colR;
	colGreen = colG;
	colBlue = colB;

	// Disable Shadows
	hasShadow = false;
}

// Updating
void Bush :: update(GraphicsOGL* gl, float deltaT) {
	Tree :: update(gl, deltaT);
}

// Drawing
void Bush :: draw(GraphicsOGL* gl, float deltaT) {

	int fidelity = 10;
	float R = 20, G = 255, B = 50;


	// If Hurt, Shake Bush
	float aX = 0, aY = 0;
	if(damageShakeTimer > -1) {
		aX = 2.*(((getTime()*rand())%100)/100. - .5);
		aY = 2.*(((getTime()*rand())%100)/100. - .5);
	}
	

	float m;
	m = 20;

	// Transform to Position
	gl->transformClear();
	gl->transformTranslation(x+aX,y+aY,z-3);
		gl->transformRotationZ(fallXYDir);
		gl->transformRotationY(fallZDir);
		gl->transformRotationZ(-fallXYDir);
	gl->transformScale(size*5,size*5,size*7);


	// Enable Shader if PC Not SLow
	if(!gl->isPCSlow())
		gl->enableShader("pineBranch");

	// If Hurt, Set Color to Red
	if(damageShakeTimer > -1)
		gl->setColor(255*colRed, .2*255*colGreen, .2*255*colBlue);
	// Otherwise, Set Color
	else
		gl->setColor(255*colRed, 255*colGreen, 255*colBlue);

	float dX, dY, dZ, dR;
	float r = 15, h = 30, uR, uH;
	dX = 0;
	dY = 0;
	dZ = 5-2;
	dR = 5;
	
	gl->setShaderVariable("iDark", 0);
	
	// Draw 3D Sphere for Base of Bush
	gl->draw3DSphere(dX,dY,dZ,dR, fidelity, branchTex);
	// Draw Sub-bushes
	for (int i = 0; i <= 3; i++) {
		float d = 1.*i/3.*360;
		dX = calcLenX(3,d);
		dY = calcLenY(3,d);

		gl->setShaderVariable("iDark", 0);

		gl->draw3DSphere(dX,dY,dZ-2,dR, fidelity, branchTex);
	}

	// Reset OpenGL Drawing to Normal
	gl->setColor(255,255,255);
	gl->disableShaders();
	gl->transformClear();
}
