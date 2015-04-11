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
//#include "../Particles/AttackSwing.h"
#include "../Environment/Heightmap.h"
#include "../Particles/SmokeRing.h"

using namespace std;

#define SH_SPHERE 0
#define SH_CONE_UP 1
#define SH_CONE_DOWN 2
#define SH_PRISM_6 3
#define SH_PRISM_5 4
#define SH_CUBE 5
#define SH_PRISM_3 6
#define SH_CYLINDER 7

#define ATTACK_TIMER_MAX 11 //12
#define KNOCKBACK_TIMER_MAX 15
#define TARGET_TIMER_MAX 50
#define TARGET_DISTANCE_MAX 200

SortedList<Character*> Character :: characterList;

float Character::GRAVITY_HOP_ACCELERATION = -.125*.75; //GRAVITY_ACCELERATION*.75;
float hopHeight = 3;
float hopSpeed = sqrt(abs(2*Character::GRAVITY_HOP_ACCELERATION*hopHeight));
float s = 6, h = 8;


Character :: Character(float x, float y, float z) : Physical(x,y,z) {

	float baseHP = rnd()*100;
	float baseAtk = rnd()*100;
	float baseDef = rnd()*100;

	level = ceil(rnd()*50);
	hp = maxHP = (baseHP + 50)*level/50 + 10;//3.*level/10;
	atk = (baseAtk)*level/50 + 5;
	def = (baseDef)*level/50 + 5;

	hopX = 0;
	faceDir = 0;
	toolDir = 0;

	isHurt = false;

	attackTimer = -1;

	knockbackTimer = -1;
	knockbackDir = 0;

	target = NULL;
	targetShift = 0;
	targetTimer = -1;

	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;
	hopDir = 1;

	shape = floor(rnd()*8);

	
	wXRot = 0;
	wYRot = 0;
	wZRot = 0;


	characterList.add(this);
}

float Character :: calcDamage(float attackPower, Character* attacker, Character* defender) {
	
	float modifier = 1.*1*1*1*(.85 + .15*rnd());

	return ((2.*attacker->level + 10)/250*(attacker->atk/defender->def)*attackPower + 2)*modifier;
}

float Character :: getHP() {
	return hp;
}

float Character :: getMaxHP() {
	return maxHP;
}

void Character :: damage(Character* attacker, float dDir) {
	if(knockbackTimer == -1) {
		hp -= calcDamage(50,attacker,this);
		knockback(dDir);
		isHurt = true;

		if(hp <= 0)
			destroy();
	}
}

void Character :: update(GraphicsOGL* gl, float deltaTime) {

	// Update Physics/Collisions
	Physical :: update(gl, deltaTime);

	collideTree();
	collideCharacter();

	updateHop(gl, deltaTime);

	if(attackTimer > -1) {
		attackTimer -= deltaTime;
		if(attackTimer <= -1)
			attackTimer = -1;
	}

	float camPos[3], camX, camY, camFOV, camDir;
		gl->getCamera()->getPosition(camPos);
		camX = camPos[0];
		camY = camPos[1];
		camDir = gl->getCamera()->getCamDir();

		camFOV = 45/2;


	// FIND TARGET
	if(targetTimer > -1) {

		targetShift += (1 - targetShift)/10;

		if(target != NULL)
			if(target->getHP() > 0) {
				if(calcPtDis(x,y,target->getX(),target->getY()) < TARGET_DISTANCE_MAX && abs(calcAngleDiff(calcPtDir(camX,camY,target->getX(),target->getY()),camDir)) < camFOV)
					targetTimer = TARGET_TIMER_MAX;	
			}
			else
				targetTimer = -1;

		targetTimer -= deltaTime;
		if(targetTimer <= -1)
			targetTimer = -1;
	}
	else {
		if(target != NULL) {
			targetShift += (0 - targetShift)/10;
		
			if(targetShift < .05)
				target = NULL;
		}
		else {
			

			for(int i = 0; i < characterList.size(); i++) {
				Character* c = characterList[i];

				if(c == this)
					continue;

				if(calcPtDis(x,y,c->getX(),c->getY()) < TARGET_DISTANCE_MAX && abs(calcAngleDiff(calcPtDir(camX,camY,c->getX(),c->getY()),camDir)) < camFOV) {
					targetTimer = TARGET_TIMER_MAX;
					target = c;
					break;
				}
			}
		}
	}

	if(knockbackTimer > -1) {
		faceDirection(knockbackDir+180);
		toolDirection(knockbackDir+180);

		direction = knockbackDir;
		vel = 1.5;

		knockbackTimer -= deltaTime;

		if(knockbackTimer <= -1) {
			vel = 0;
			isHurt = false;
			knockbackTimer = -1;
		}
	}
}

void Character :: attack() {
	if(attackTimer > -1)
		return;

	SoundController::playSound("swordSwing",this);
	//new AttackSwing(x,y,z,toolDirection);

	attackTimer = ATTACK_TIMER_MAX;

	float atkAng = 90;
	float atkX, atkY, atkR;
	atkX = x;
	atkY = y;
	atkR = s + 10*1.3;

	// Attack Trees
	for(int i = 0; i < Tree::treeList.size(); i++) {
		Tree* t = Tree::treeList[i];

		float tX = t->getX(), tY = t->getY();
		float dis = calcPtDis(atkX,atkY,tX,tY);
		float tS = t->getSize()*5;

		if(dis < (atkR + tS)) {
			float dir = calcPtDir(atkX,atkY,tX,tY);
			if(abs(calcAngleDiff(dir, toolDir)) < atkAng) {
				SoundController::playSound("swordHitWood",this);
				t->damage(dir);
				knockback(dir+180);
				break;
			}
		}
	}

	for(int i = 0; i < characterList.size(); i++) {
		Character* c = characterList[i];

		if(c != this) {

			float cX = c->getX(), cY = c->getY();
			float dis = calcPtDis(atkX,atkY,cX,cY);
			float cS = s;//t->getSize()*5;

			if(dis < (s*2 + cS)) {
				float dir = calcPtDir(atkX,atkY,cX,cY);
				if(abs(calcAngleDiff(dir, toolDir)) < atkAng) {
					SoundController::playSound("swordHitFlesh",this);
					SoundController::playSound("attackCollision",this);
					c->damage(this,dir);

					target = c;
					targetTimer = TARGET_TIMER_MAX;
				}
			}
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


	/*gl->setDepthTest(false);
		gl->transformTranslation(x,y,grndZ);
		gl->transformRotationZ(setupRot);
		gl->transformRotationX(xyRot);	

		gl->transformScale(1 - (z-grndZ)/70);	

		gl->draw3DFloor(-8,-8,8,8,0,gl->getTextureController()->getTexture("Shadow"));

		gl->transformClear();
	gl->setDepthTest(true);*/


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

	if(!gl->isPCSlow())
		gl->enableShader("Character");	
	gl->transformTranslation(x,y,z+hopZ);
	
	if(onGround/*&& hopZ <= 0*/) {
		gl->transformRotationZ(setupRot);	
		gl->transformRotationX(xyRot);
		gl->transformRotationZ(-setupRot);


		gl->transformRotationZ(faceDir);
		gl->transformRotationX(-hopX*10);		
		gl->transformRotationY(-hopZVel*10);		
		gl->transformTranslation(-hopZVel,hopX,0);	
	}
	else
		gl->transformRotationZ(faceDir);

	//gl->transformTranslation(-hopZVel,hopX,0);
	gl->transformScale(hopSc,hopSc,1/hopSc);


	gl->setShaderVariable("cDirection", faceDir/180.*3.14159);
	if(isHurt)
		gl->setShaderVariable("iHit", abs(sin(knockbackTimer)));
	else
		gl->setShaderVariable("iHit",0);


	if(shape == SH_PRISM_6)
		gl->draw3DPrism(0,0,0,s,h,6);
	else if(shape == SH_PRISM_5)
		gl->draw3DPrism(0,0,0,s,h,5);
	else if(shape == SH_PRISM_3)
		gl->draw3DPrism(0,0,0,s,h,3);
	else if(shape == SH_CUBE)
		gl->draw3DPrism(0,0,0,s,h,4);
	else if(shape == SH_SPHERE)
		gl->draw3DSphere(0,0,s,s,13);
	else if(shape == SH_CONE_DOWN)
		gl->draw3DCone(0,0,h,s,-h,13);
	else if(shape == SH_CONE_UP)
		gl->draw3DCone(0,0,0,s,h,13);
	else if(shape == SH_CYLINDER)
		gl->draw3DPrism(0,0,0,s,h,13);

	gl->transformClear();

		// Draw Weapon
		gl->transformTranslation(x,y,z+hopZ);
	
		if(onGround/*&& hopZ <= 0*/) {
			gl->transformRotationZ(setupRot);	
			gl->transformRotationX(xyRot);
			gl->transformRotationZ(-setupRot);


			gl->transformRotationZ(faceDir);		
			gl->transformTranslation(-hopZVel,hopX,0);	
			gl->transformTranslation(-3*hopZVel,3*hopX,0);
			gl->transformRotationZ(-faceDir);		
		}
		
		if(attackTimer == -1)
			gl->transformRotationZ(toolDir);
		else {
			//Animation #1
			// Stab
			/*gl->transformRotationZ(toolDir);

			float timerPerc = pow(attackTimer/ATTACK_TIMER_MAX,2.);


			gl->transformTranslation(7,-6,3);
			gl->transformRotationY(90*timerPerc);
			gl->transformTranslation(-7,6,-3);

			gl->transformRotationZ(90*timerPerc);*/

			//Animation #2
			gl->transformRotationZ(toolDir);

			float timerPerc = attackTimer/ATTACK_TIMER_MAX;			
				float mTimerPerc = pow(abs(sin(3.14159*(1-timerPerc))),.3);

			//timerPerc = min(1.,1-2*timerPerc);

			float tTimerPerc = min(1.,attackTimer/(ATTACK_TIMER_MAX*.75));
			tTimerPerc = 1.-tTimerPerc;

			float nXRot, nYRot, nZRot;
			nXRot = mTimerPerc*(20*cos(3.14159*tTimerPerc));
			nYRot = mTimerPerc*(90 + 5*cos(3.14159*tTimerPerc));

			//tTimerPerc += (1 - tTimerPerc)/pow(1+timerPerc,.5);
			nZRot = mTimerPerc*(180*(-.5 + tTimerPerc));

			float f = 1+2*(1.-mTimerPerc);

			wXRot += (nXRot - wXRot)/f;
			wYRot += (nYRot - wYRot)/f;
			wZRot += (nZRot - wZRot)/f;

			gl->transformRotationZ(wZRot);

			gl->transformTranslation(7,-6,3);
			gl->transformRotationY(wYRot);
			gl->transformRotationX(wXRot);
			gl->transformTranslation(-7,6,-3);

		}

		float upF = knockbackTimer/KNOCKBACK_TIMER_MAX;
		float upZ = 10*pow(sin(upF*3.14159),.125)*pow(1-upF,.8);

		if(!isHurt)
			upZ = 0;

		gl->transformTranslation(7,-6,3 + upZ);

		gl->transformScale(1,1,1.3);

		gl->setShaderVariable("cDirection", toolDir/180.*3.14159);
		if(isHurt)
			gl->setShaderVariable("iHit", abs(sin(knockbackTimer)));
		else
			gl->setShaderVariable("iHit",0);


		// Hilt
		gl->draw3DPrism(0,0,.5,.5,2,3);
		gl->draw3DBlock(-.8,-2,2,.8,2,3);

		// Blade
		gl->draw3DCone(0,0,7,1,3,3);
		gl->draw3DFrustem(0,0,2,.8,1,5,3);




	gl->transformClear();



	gl->disableShaders();
	gl->setColor(255,255,255);
}

/*string to_string(float num) {
	return to_string(static_cast<long float>(num));
}*/

void Character :: drawStatWindow(GraphicsOGL* gl, float perc) {

	float oX, oY, dX, dY, w = 200, h = 200;
	dX = oX = 640-w*perc;
	dY = oY = 480-h;
	dX += 16;
	dY += 16;

	string diff, shp;

	if(level < 10)
		diff = "Weak";
	else if(level < 20)
		diff = "Intermediate";
	else if(level < 30)
		diff = "Skilled";
	else if(level < 40)
		diff = "Master";
	else
		diff = "Legend";
	
	switch(shape) {
		case SH_PRISM_6: 
			shp = "Hex"; break;
		case SH_PRISM_5:
			shp = "Pent"; break;
		case SH_PRISM_3:
			shp = "Tri"; break;
		case SH_CUBE:
			shp = "Cube"; break;
		case SH_SPHERE:
			shp = "Sphere"; break;
		case SH_CONE_DOWN:
			shp = "Inverse Cone"; break;
		case SH_CONE_UP:
			shp = "Cone"; break;
		case SH_CYLINDER:
			shp = "Cylinder"; break;
	}
	
	gl->setColor(255,255,255);
	gl->drawString(dX,dY,"  " + diff + " " + shp);
		dY += 25;


	int at, de, he, mHe;
	at = atk;	
	de = def;
	he = hp;
	mHe = maxHP;

	gl->drawString(dX,dY,"Lvl: " + to_string(level));
		dY += 15;
	gl->drawString(dX,dY,"Atk: " + to_string(at));
		dX += w/2-16;
	gl->drawString(dX,dY,"Def: " + to_string(de));
		dX = oX+16;
		dY += 15;
	gl->drawString(dX,dY,"HP: " + to_string(he) + " / " + to_string(mHe));

		dY += 15;
	gl->drawHealth(dX,dY,he,mHe);

		dY += 15;
	

	gl->setColor(20,20,20);
	gl->drawRect(oX,oY,oX+w,oY+h);

	gl->setColor(180,180,180);
	gl->drawRect(oX+1,oY+1,oX+w-1,oY+h-1);

	gl->setColor(20,20,20,200);
	gl->fillRect(oX,oY,oX+w,oY+h);
}

void Character :: destroy() {
	Physical :: destroy();

	characterList.destroy(this);
}

void Character :: faceDirection(float dir) {
	faceDir += calcTurnToDir(faceDir,dir);
}

void Character :: toolDirection(float dir) {
	toolDir = dir;//+= calcTurnToDir(toolDir,dir);
}

void Character :: knockback(float kDir) {

	if(knockbackTimer == -1) {
		knockbackDir = kDir;
		knockbackTimer = KNOCKBACK_TIMER_MAX;

		zVel = 1.5;
	}
}


void Character :: updateHop(GraphicsOGL* gl, float deltaT) {
	float hopZVelP = hopZVel;
	float chAmt = 10;

	if(onGround) {
		hopZVel += GRAVITY_HOP_ACCELERATION;
		hopZ += hopZVel;
		if(hopZ <= 0) {
			if(hopZVel != GRAVITY_HOP_ACCELERATION) {
				new SmokeRing(x,y,z,2,8,4,1.3);
				SoundController::playSound("fsGrass",this);
			}

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


void Character :: land(GraphicsOGL* gl) {

	hopSc *= 2;
	new SmokeRing(x,y,z,4,13,7,2);
	SoundController::playSound("fsGrass");
}
