// Character.cpp


#include <deque>
#include <string>
#include <iostream>
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "Character.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;



float hopSpeed = sqrt(abs(2*Physical::GRAVITY_ACCELERATION*3));
float s = 6, h = 8;

Texture* Character :: shTex;

Character :: Character(float x, float y, float z) : Physical(x,y,z) {

	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;

 	shTex = new Texture("Resources/Images/shadow.png",false);
}

void Character :: update(GraphicsOGL* gl, float deltaTime) {

	// Update Physics/Collisions
	Physical :: update(gl, deltaTime);


	updateHop(deltaTime);
}

void Character :: draw(GraphicsOGL* gl, float deltaTime) {

	//Physical :: draw(gl, deltaTime);

	Heightmap* hm = gl->getHeightmap();

	float sideNum = 6;

	float normal[3];
	float xyDis, nX, nY, nZ, xRot, yRot, setupRot, xyRot;

		hm->getNormal(x,y,normal);
		
			nX = normal[0];
			nY = normal[1];
			nZ = normal[2];


		xyDis = sqrt(nX*nX + nY*nY);
		xRot = 90 - (180-(90+calcPtDir(0,0,nX,nZ)));
		yRot = calcPtDir(0,0,nY,nZ);

		setupRot = 90+calcPtDir(0,0,nX,nY);
		xyRot = 90-calcPtDir(0,0,xyDis,nZ);



	// Draw Several Shadows
	/*for(int i = 0; i < 4; i++) {
		float shNorm[3];
		float l = s, d = i*90., shadowX = x + calcLenX(l,d), shadowY = y + calcLenY(l,d), shadowZ = hm->getHeightXY(shadowX,shadowY);
		float shadowSetupRot, shadowXYRot;

			hm->getNormal(shadowX, shadowY, shNorm);

		shadowSetupRot = 90+calcPtDir(0,0,shNorm[0],shNorm[1]);
		shadowXYRot = 90-calcPtDir(0,0,calcPtDis(0,0,shNorm[0],shNorm[1]),shNorm[2]);

		//DRAW SHADOW
			glTranslatef(x,y,z+.3);
			glRotated(shadowSetupRot, 0, 0, 1);	
			glRotated(shadowXYRot, 1, 0, 0);
	
			gl->draw3DFloor(-8,-8,8,8,0,shTex);

			glLoadIdentity();
	}*/


	// Draw Sky
	gl->enableShader("Sky");
		gl->transformTranslation(x,y,z);

		float sc = 2000;

		gl->draw3DFloor(-sc,-sc,sc,sc,sc);
		gl->draw3DWall(-sc,-sc,sc,sc,-sc,-sc);
		gl->draw3DWall(-sc,sc,sc,sc,sc,-sc);
		gl->draw3DWall(-sc,-sc,sc,-sc,sc,-sc);
		gl->draw3DWall(sc,-sc,sc,sc,sc,-sc);
		gl->transformClear();
	gl->disableShaders();


	gl->transformTranslation(x,y,z+hopZ);

	if(onGround && hopZ <= 0) {
		gl->transformRotationZ(setupRot);	
		gl->transformRotationX(xyRot);
		gl->transformRotationZ(direction-setupRot);	
	}
	else
		gl->transformRotationZ(direction);	
	
	gl->transformScale(hopSc,hopSc,1/hopSc);

	gl->draw3DPrism(0,0,0,s,h,6);


	gl->disableShaders();
	gl->transformClear();
}


void Character :: updateHop(float deltaT) {
	float hopZVelP = hopZVel;

	if(onGround) {
		hopZVel += GRAVITY_ACCELERATION;
		hopZ += hopZVel;
		if(hopZ < 0) {
			hopZ = hopZVel = 0;

			if(hopZVelP != 0)
				hopSc *= 1.3;
		}

		hopSc += (1 - hopSc)/3;
	}
	else {
		hopZ = 0;
		hopZVel = 0;
		hopSc += (1 - hopSc)/3;
	}
}

void Character :: hop() {
	if(hopZ == 0)
		hopZVel = hopSpeed;
}


void Character :: land() {
}
