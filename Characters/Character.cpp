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
#include "../Particles/SmokeRing.h"
using namespace std;



float Character::GRAVITY_HOP_ACCELERATION = GRAVITY_ACCELERATION*.5;
float hopHeight = 3;
float hopSpeed = sqrt(abs(2*Character::GRAVITY_HOP_ACCELERATION*hopHeight));
float s = 6, h = 8;

Texture* Character :: shTex;

Character :: Character(float x, float y, float z) : Physical(x,y,z) {

	hopX = 0;
	faceDir = 0;
	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;
	hopDir = 1;
	hopX = 0;

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
		//gl->transformRotationX(xyRot);
		gl->transformRotationZ(faceDir-setupRot);	
	}
	else
		gl->transformRotationZ(faceDir);

	gl->transformTranslation(-hopZVel,hopX,0);
	gl->transformScale(hopSc,hopSc,1/hopSc);

	gl->draw3DPrism(0,0,0,s,h,6);


	gl->disableShaders();
	gl->transformClear();
}

void Character :: faceDirection(float dir) {
	faceDir += calcTurnToDir(faceDir,dir);
}


void Character :: updateHop(float deltaT) {
	float hopZVelP = hopZVel;
	float chAmt = 5;

	if(onGround) {
		hopZVel += GRAVITY_HOP_ACCELERATION;
		hopZ += hopZVel;
		if(hopZ < 0) {
			hopZ = hopZVel = 0;

			if(hopZVelP != 0)
				hopSc *= 1.3;
		}

		hopSc += (1 - hopSc)/3;

		if(isMoving)
			hopX += ((3*hopDir*(hopHeight-hopZ)/hopHeight) - hopX)/chAmt;
	}
	else {
		hopZ = 0;
		hopZVel = 0;
		hopSc += (1 - hopSc)/3;
	}

	if(!isMoving || !onGround)
		hopX += (0 - hopX)/chAmt;
}

void Character :: hop() {
	if(hopZ == 0) {
		hopZVel = hopSpeed;

		cout << hopDir << ", " << hopX << endl;

		hopDir *= -1;
	}
}


void Character :: land() {
	new SmokeRing(x,y,z,4,12,20);
}