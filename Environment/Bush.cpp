// Bush.cpp

#include "../Graphics/GraphicsOGL.h"
#include "Bush.h"
#include "../Functions/Math2D.h"
#include "Tree.h"
#include "../Graphics/Texture.h"





Bush :: Bush(float nX, float nY, float size, float colR, float colG, float colB) : Tree(nX,nY,size) {

	colRed = colR;
	colGreen = colG;
	colBlue = colB;

	hasShadow = false;
}

void Bush :: update(GraphicsOGL* gl, float deltaT) {
	Tree :: update(gl, deltaT);
}

void Bush :: draw(GraphicsOGL* gl, float deltaT) {

	int fidelity = 10;
	float R = 20, G = 255, B = 50;


	//DRAW SHADOW
	float xyDis, nX, nY, nZ, xRot, yRot, setupRot, xyRot;

	/*	gl->getHeightmap()->getFloorRotations(x,y,setupRot,xyRot);
	float grndZ = z;

	gl->setCulling(true);
	gl->setDepthTest(false);
		gl->transformTranslation(x,y,grndZ);
		gl->transformRotationZ(setupRot);
		gl->transformRotationX(xyRot);	

		gl->transformScale(size);	

		float s = 32;
		gl->draw3DFloor(-s,-s,s,s,0,gl->getTextureController()->getTexture("Shadow"));

		gl->transformClear();
	gl->setCulling(false);
	gl->setDepthTest(true);*/


	float aX = 0, aY = 0;
	if(damageShakeTimer > -1) {
		aX = 2.*(((getTime()*rand())%100)/100. - .5);
		aY = 2.*(((getTime()*rand())%100)/100. - .5);
	}
	

	float m;
	m = 20;

	gl->transformClear();
	gl->transformTranslation(x+aX,y+aY,z-3);
		gl->transformRotationZ(fallXYDir);
		gl->transformRotationY(fallZDir);
		gl->transformRotationZ(-fallXYDir);
	gl->transformScale(size*5,size*5,size*7);

	Texture* branchTex = gl->getTextureController()->getTexture("pineBranch");
	Texture* barkTex = gl->getTextureController()->getTexture("bark");

	
	/*float bR, bG, bB;
		bR = 255*(colGreen);
		bG = 255*(1-colGreen);
		bB = 255*(1-colGreen);

	gl->setColor(bR,bG,bB);*/

	/*gl->enableShader("pineBark");
	gl->draw3DPrism(0,0,0,4,30, fidelity, barkTex);
	gl->draw3DCone(0,0,0,5,30, fidelity, barkTex);*/
	if(!gl->isPCSlow())
		gl->enableShader("pineBranch");

	if(damageShakeTimer > -1)
		gl->setColor(255*colRed, .2*255*colGreen, .2*255*colBlue);
	else
		gl->setColor(255*colRed, 255*colGreen, 255*colBlue);

	float dX, dY, dZ, dR;
	float r = 15, h = 30, uR, uH;
	dX = 0;
	dY = 0;
	dZ = 5-2;
	dR = 5;
	
	gl->setShaderVariable("iDark", 0);
	gl->draw3DSphere(dX,dY,dZ,dR, fidelity, branchTex);
	for (int i = 0; i <= 3; i++) {
		//dR -= 2;

		float d = 1.*i/3.*360;
		dX = calcLenX(3,d);
		dY = calcLenY(3,d);

		
		gl->setShaderVariable("iDark", 0);

		gl->draw3DSphere(dX,dY,dZ-2,dR, fidelity, branchTex);
	}

	gl->setColor(255,255,255);
	gl->disableShaders();

	gl->transformClear();
}
