// Character.cpp


#include <deque>
#include <string>
#include <iostream>
#include "../Environment/Tree.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "Character.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
#include "../Particles/SmokeRing.h"
using namespace std;


SortedList<Character*> Character :: characterList;

float Character::GRAVITY_HOP_ACCELERATION = -.125*.75; //GRAVITY_ACCELERATION*.75;
float hopHeight = 3;
float hopSpeed = sqrt(abs(2*Character::GRAVITY_HOP_ACCELERATION*hopHeight));
float s = 6, h = 8;


Character :: Character(float x, float y, float z) : Physical(x,y,z) {

	hopX = 0;
	faceDir = 0;
	toolDir = 0;

	knockbackTimer = -1;
	knockbackDir = 0;

	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;
	hopDir = 1;

	characterList.add(this);
}

void Character :: update(GraphicsOGL* gl, float deltaTime) {

	// Update Physics/Collisions
	Physical :: update(gl, deltaTime);

	collideTree();
	collideCharacter();

	updateHop(deltaTime);

	if(gl->getInputController()->checkLetter('y'))
		knockback(0);

	if(knockbackTimer > -1) {
		faceDirection(knockbackDir+180);
		toolDirection(knockbackDir+180);

		direction = knockbackDir;
		vel = 1.5;

		knockbackTimer -= deltaTime;

		if(knockbackTimer <= -1) {
			vel = 0;
			knockbackTimer = -1;
		}
	}
}

void Character :: collideTree() {
	for(int i = 0; i < Tree::treeList.size(); i++) {
		Tree* t = Tree::treeList[i];

		float tX = t->getX(), tY = t->getY();
		float dis = calcPtDis(x,y,tX,tY);
		float tS = t->getSize()*5;

		if(dis < (s + tS)) {
			float dir = calcPtDir(x,y,tX,tY);

			float cNX, cNY, vNX, vNY;
			cNX = calcLenX(1, dir);
			cNY = calcLenY(1, dir);

			float aX, aY;
			aX = calcLenX(tS+s, dir);
			aY = calcLenY(tS+s, dir);

			x = tX - aX;
			y = tY - aY;

			float friction = .5;
			vel *= friction;
		}
	}
}

void Character :: collideCharacter() {
	for(int i = 0; i < characterList.size(); i++) {
		Character* c = characterList[i];

		if(c != this) {
			float dis = calcPtDis(x,y,c->x,c->y);

			if(dis < 2*s) {
				float dir = calcPtDir(x,y,c->x,c->y);
				float hX, hY;
				hX = (x + c->x)/2;
				hY = (y + c->y)/2;


				float cNX, cNY, vNX, vNY;
				cNX = calcLenX(1, dir);
				cNY = calcLenY(1, dir);

				vNX = calcLenX(1, direction);
				vNY = calcLenY(1, direction);

				float pref, p;
				pref = abs(cNX*vNX + cNY*vNY);
	
				if(pref > .5)
					p = 1;
				else
					p = 0;

				float aX, aY;
				aX = calcLenX(s, dir);
				aY = calcLenY(s, dir);


				x = hX - aX;
				y = hY - aY;
				c->x = hX + aX;
				c->y = hY + aY;


				/*if(vel > c->vel) {
					c->x = x + aX;
					c->y = y + aY;
				}
				else {
					x = c->x - aX;
					y = c->y - aY;
				}*/

				float friction = .5;
				vel *= friction;
				c->vel *= friction;
			}
		}
	}
}

void Character :: draw(GraphicsOGL* gl, float deltaTime) {

	//Physical :: draw(gl, deltaTime);

	Heightmap* hm = gl->getHeightmap();

	float sideNum = 6;

	float xyDis, nX, nY, nZ, xRot, yRot, setupRot, xyRot;

		hm->getFloorRotations(x,y,setupRot,xyRot);

	//DRAW SHADOW
	float grndZ = hm->getHeightXY(x,y);

	gl->setDepthTest(false);
		gl->transformTranslation(x,y,grndZ);
		gl->transformRotationZ(setupRot);
		gl->transformRotationX(xyRot);	

		gl->transformScale(1 - (z-grndZ)/70);	

		gl->draw3DFloor(-8,-8,8,8,0,gl->getTextureController()->getTexture("Shadow"));

		gl->transformClear();
	gl->setDepthTest(true);

	/*
	// Draw Several Shadows
	for(int i = 0; i < 4; i++) {
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
	}
	gl->glSet();
	*/

	
	gl->transformTranslation(x,y,z+hopZ);
	


	if(onGround/*&& hopZ <= 0*/) {
		gl->transformRotationZ(setupRot);	
		gl->transformRotationX(xyRot);
		gl->transformRotationZ(-setupRot);


		gl->transformRotationZ(faceDir);		
		gl->transformTranslation(-hopZVel,hopX,0);	
	}
	else
		gl->transformRotationZ(faceDir);

	//gl->transformTranslation(-hopZVel,hopX,0);
	gl->transformScale(hopSc,hopSc,1/hopSc);

	gl->enableShader("Character");
	gl->setShaderVariable("cDirection", faceDir/180.*3.14159);

	gl->draw3DPrism(0,0,0,s,h,6);

	gl->disableShaders();

	gl->disableShaders();
	gl->transformClear();
}

void Character :: destroy() {
	Physical :: destroy();

	characterList.destroy(this);
}

void Character :: faceDirection(float dir) {
	faceDir += calcTurnToDir(faceDir,dir);
}

void Character :: toolDirection(float dir) {
	toolDir += calcTurnToDir(toolDir,dir);
}

void Character :: knockback(float kDir) {
	knockbackDir = kDir;
	knockbackTimer = 15;

	zVel = 1;
}


void Character :: updateHop(float deltaT) {
	float hopZVelP = hopZVel;
	float chAmt = 10;

	if(onGround) {
		hopZVel += GRAVITY_HOP_ACCELERATION;
		hopZ += hopZVel;
		if(hopZ <= 0) {
			if(hopZVel != GRAVITY_HOP_ACCELERATION)
				new SmokeRing(x,y,z,2,8,4,1.3);

			hopZ = hopZVel = 0;

			if(hopZVelP != 0)
				hopSc *= 1.3;
		}

		hopSc += (1 - hopSc)/3;

		if(isMoving)
			hopX += ((2*hopDir*(hopHeight-hopZ)/hopHeight) - hopX)/chAmt;
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

		hopDir *= -1;
	}
}


void Character :: land() {

	hopSc *= 2;
	new SmokeRing(x,y,z,4,13,7,2);
}
