// Character.cpp
// Ryan McGrail

#include <deque>
#include <string>
#include <iostream>
#include <cmath>
#include "../Environment/Tree.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "Character.h"
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
#include "../Particles/SmokeRing.h"
#include "../Particles/DeathPuff.h"
using namespace std;


// Define All Possible Character Shapes
#define SH_SPHERE 0
#define SH_CONE_UP 1
#define SH_CONE_DOWN 2
#define SH_PRISM_6 3
#define SH_PRISM_5 4
#define SH_CUBE 5
#define SH_PRISM_3 6
#define SH_CYLINDER 7
#define SH_DIAMOND 8

// Define Timer Maxes
#define ATTACK_TIMER_MAX 11
#define KNOCKBACK_TIMER_MAX 15
#define TARGET_TIMER_MAX 50
#define DESTROY_TIMER_MAX 60
#define DESTSHR_TIMER_MAX 25

// Define Max Target Distance
#define TARGET_DISTANCE_MAX 200


// Static Character list
SortedList<Character*> Character :: characterList;

// Gravity for Hopping
float Character::GRAVITY_HOP_ACCELERATION = -.125*.75;

// Calculate Jumping Speed for Hopping
float hopHeight = 3;
float hopSpeed = sqrt(abs(2*Character::GRAVITY_HOP_ACCELERATION*hopHeight));

// Height of Character
float h = 8;


// Constructor
Character :: Character(float x, float y, float z) : Physical(x,y,z) {

	// Randomize Color
	appearanceR = rnd();
	appearanceG = rnd();
	appearanceB = rnd();
	
	// Randomize Scale
	appearanceXScale = rnd(.9,1.1);
	appearanceYScale = rnd(.9,1.1);
	appearanceZScale = rnd(.9,1.1);

	// Radius
	size = 6;

	// Randomize Stats
	float baseHP = rnd()*100;
	float baseAtk = rnd()*100;
	float baseDef = rnd()*100;
	level = ceil(rnd()*50);
	hp = maxHP = (baseHP + 50)*level/50 + 10;//3.*level/10;
	atk = (baseAtk)*level/50 + 5;
	def = (baseDef)*level/50 + 5;

	// Initialize Hop Variables
	hopX = 0;
	hopZ = 0;
	hopZVel = 0;
	hopSc = 1;
	hopDir = 1;
	
	// Initialize Directions
	faceDir = 0;
	toolDir = 0;

	// Initialize Attack Timer
	attackTimer = -1;

	// Initialize Knockback Vars
	isHurt = false;
	knockbackTimer = -1;
	knockbackDir = 0;

	// Initialize Target Vars
	target = NULL;
	targetShift = 0;
	targetTimer = -1;

	// Initialize Destroy Vars
	destroyShrTimer = destroyTimer = destroyToX = destroyToY = destroyToZ = -1;

	// Randomize Shape
	shape = floor(rnd()*9);

	// Initialize Weapon Rots
	wXRot = 0;
	wYRot = 0;
	wZRot = 0;

	// Get Sword Texture
	swordHiltTex = TextureController::getTexture("bark");

	// Add to Character List
	characterList.add(this);
}


// Taking Damage
void Character :: damage(Character* attacker, float dDir) {
	// If Not Knocked Back or Dead,
	if(hp > 0 && knockbackTimer == -1) {
	
		// Damage and Knockback
		hp -= calcDamage(50,attacker,this);
		knockback(dDir);
		isHurt = true;

		// If Dead, Start Dying
		if(hp <= 0) {
			SoundController::playSound("exploding",this);
			
			//Start Dying Animation
			destroyTimer = DESTROY_TIMER_MAX;
			destroyToX = x + calcLenX(5,dDir);
			destroyToY = y + calcLenY(5,dDir);
			destroyToZ = z + 2;
		}
	}
}

// INHERITED FUNCTIONS
	void Character :: update(GraphicsOGL* gl, float deltaTime) {

		// If Dying, Move Up to Destroy Position
		if(destroyTimer > -1) {
			x += (destroyToX - x)/10;
			y += (destroyToY - y)/10;
			z += (destroyToZ - z)/10;

			destroyTimer -= deltaTime;

			// If Destroying Timer Done, Play Death Sound
			if(destroyTimer <= -1) {
				SoundController::playSound("death",this);
				destroyTimer = -2;
				destroyShrTimer = 1;
			}
			return;
		}
		// Shrink Player Quickly Before Exploding
		else if(destroyTimer == -2) {

			destroyShrTimer += (0 - destroyShrTimer)/1.5;

			if(destroyShrTimer < .01)
				destroy();

			return;
		}


		// Update Physics/Collisions
		Physical :: update(gl, deltaTime);

		// Collide w/ Trees & Characters
		collideTree();
		collideCharacter();

		// Updating Hopping
		updateHop(gl, deltaTime);

		// If Attacking, Decrease Timer
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
		// If TargetTimer > -1, Already Have Target
		if(targetTimer > -1) {

			// Move Stats Window on Screen
			targetShift += (1 - targetShift)/10;

			// If Target Still Exists, 
			if(target != NULL)
				// If Not Dead,
				if(target->getHP() > 0) {
					// If Close, Keep Target Timer Up (Keep them as Target)
					if(calcPtDis(x,y,target->getX(),target->getY()) < TARGET_DISTANCE_MAX && abs(calcAngleDiff(calcPtDir(camX,camY,target->getX(),target->getY()),camDir)) < camFOV)
						targetTimer = TARGET_TIMER_MAX;	
				}
				else
					targetTimer = -1;

			// Decrease Target Timer Over Time (If Reaches -1, Target is Too Far Away or Offscreen)
			targetTimer -= deltaTime;
			if(targetTimer <= -1)
				targetTimer = -1;
		}
		else {
			// If Target Not Null, Move Stats Offscreen
			if(target != NULL) {
				targetShift += (0 - targetShift)/10;
			
				if(targetShift < .05)
					target = NULL;
			}
			// Otherwise, Try to Find Target
			else for(int i = 0; i < characterList.size(); i++) {
				Character* c = characterList[i];

				// Ignore if Character is Self
				if(c == this)
					continue;

				// If Character is Close and Onscreen, Make as New Target
				if(calcPtDis(x,y,c->getX(),c->getY()) < TARGET_DISTANCE_MAX && abs(calcAngleDiff(calcPtDir(camX,camY,c->getX(),c->getY()),camDir)) < camFOV) {
					targetTimer = TARGET_TIMER_MAX;
					target = c;
					break;
				}
			}
		}

		// Animate Knockback
		if(knockbackTimer > -1) {
		
			// Force Direction to Face Away from Knockback
			faceDirection(knockbackDir+180);
			toolDirection(knockbackDir+180);
			direction = knockbackDir;
			vel = 1.5;

			// Lower Knockback Timer
			knockbackTimer -= deltaTime;

			// If Timer < -1, End Animation
			if(knockbackTimer <= -1) {
				vel = 0;
				isHurt = false;
				knockbackTimer = -1;
			}
		}
	}
	
	// Destroy
	void Character :: destroy() {
		
		float dX,dY,dZ, si, sm;
		float xD, yD;
		si = .2;
		sm = 20;
			
		// Create Explosion of Particles
			xD = calcLenX(1,faceDir);
			yD = calcLenY(1,faceDir);

			for(float xi = 0; xi < 1; xi += si)
				for(float yi = 0; yi < 1; yi += si) 
					for(float zi = 0; zi < 1; zi += si) {
						dX = x;
						dY = y;
						dZ = z;

						// Create New Particle at X, to Some Direction Out (Sphere-Shape)
						new DeathPuff(dX,dY,dZ, 2*(xi-.5), 2*(yi-.5),2*(zi-.5),.5, 20);
					}


		// Destroy Self in Physical List, and in Character List
		Physical :: destroy();
		characterList.destroy(this);
	}

// Attacking
void Character :: attack() {
	// If Already Attacking, Quit
	if(attackTimer > -1)
		return;

	// Play Attacking Sound
	SoundController::playSound("swordSwing",this);

	attackTimer = ATTACK_TIMER_MAX;

	float atkAng = 90;
	float atkX, atkY, atkR;
	atkX = x;
	atkY = y;
	atkR = size + 10*1.3;

	// Attack Trees
	for(int i = 0; i < Tree::treeList.size(); i++) {
		Tree* t = Tree::treeList[i];

		float tX = t->getX(), tY = t->getY();
		float dis = calcPtDis(atkX,atkY,tX,tY);
		float tS = t->getSize()*5;

		// If within Attacking Distance...
		if(dis < (atkR + tS)) {
			float dir = calcPtDir(atkX,atkY,tX,tY);
			// If Sword is Facing Tree, Damage it
			if(abs(calcAngleDiff(dir, toolDir)) < atkAng) {
				SoundController::playSound("swordHitWood",this);
				t->damage(dir);
				knockback(.25,dir+180);
				break;
			}
		}
	}

	// Attack Characters
	for(int i = 0; i < characterList.size(); i++) {
		Character* c = characterList[i];

		// Ensure Character we're Attacking isn't Ourself!
		if(c != this) {
			float cX = c->getX(), cY = c->getY();
			float cS = 6, safety = 3;

			// If Not Above or Below...
			if(z+h >= c->z+safety && z <= c->z+h-safety) {
				float dis = calcPtDis(atkX,atkY,cX,cY);

				// If Within Attacking Distance...
				if(dis < (size + c->size + cS)) {
					float dir = calcPtDir(atkX,atkY,cX,cY);
					
					// If Facing Character, Attack
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

}

// Collide w/ Trees
void Character :: collideTree() {

	// Loop Through Trees
	for(int i = 0; i < Tree::treeList.size(); i++) {
		Tree* t = Tree::treeList[i];

		// Get Tree Position, Distance, Radius
		float tX = t->getX(), tY = t->getY();
		float dis = calcPtDis(x,y,tX,tY);
		float tS = t->getSize()*5;

		// If Inside Tree...
		if(dis < (size + tS)) {
			float dir = calcPtDir(x,y,tX,tY);

			// Move Player Out of Tree
			float aX, aY;
			aX = calcLenX(tS+size, dir);
			aY = calcLenY(tS+size, dir);
			x = tX - aX;
			y = tY - aY;

			// Slow Player
			float friction = .5;
			vel *= friction;
		}
	}
}

// Collide w/ Characters
void Character :: collideCharacter() {

	// Loop through Characters
	for(int i = 0; i < characterList.size(); i++) {
		Character* c = characterList[i];

		// If Character is Not This, then Collide w/ It
		if(c != this) {
			float dis = calcPtDis(x,y,c->x,c->y);

			// If Close Enough to Collide w/
			if(dis < (size + c->size)) {

				float safety = 2;
				// Landing on Top
				if(z <= c->z+h+safety && zP >= c->z+h-safety) {
				
					// Move Along w/ Character as it Moves
					x += c->x-c->xP;
					y += c->y-c->yP;
					z += c->z-c->zP;
					zP = c->z+h;
					
					// Consider this Ground
					placeOnGround();

					// Allow "Steering"
					c->direction = toolDir;
					c->faceDir = toolDir;
					c->toolDir = toolDir;
				}
				// Colliding w/ Side
				else if(z+h >= c->z && z <= c->z+h) {
					float dir = calcPtDir(x,y,c->x,c->y);
					
					// Dtermine Halfway Point
					float hX, hY;
					hX = (x + c->x)/2;
					hY = (y + c->y)/2;

					// Move Characters
					float aX, aY;
					aX = calcLenX(1, dir);
					aY = calcLenY(1, dir);
					
					x = hX - aX*size;
					y = hY - aY*size;
					c->x = hX + aX*c->size;
					c->y = hY + aY*c->size;
				}
			}
		}
	}
}

// Drawing Character
void Character :: draw(GraphicsOGL* gl, float deltaTime) {

	Heightmap* hm = gl->getHeightmap();

	float xyDis, nX, nY, nZ, xRot, yRot, setupRot, xyRot;

	// Get Ground Rotation
	if((hm->getHeightXY(x,y)-z < .2))
		hm->getFloorRotations(x,y,setupRot,xyRot);
	else {
		setupRot = 0;
		xyRot = 0;
	}

	float destShrSc;
	
	// When Knocked Back, Move Weapon Up (upZ) and Scale Model Vertically (scZ)
	float upF = knockbackTimer/KNOCKBACK_TIMER_MAX;
	float upZ = 10*pow(sin(upF*3.14159),.125)*pow(1-upF,.8);
	float scZ = .5*sin(upF*6*3.14159);

	if(!isHurt) {
		upZ = 0;
		scZ = 0;
	}

	// Expanding Before Dying
	if(destroyTimer > -1)
		destShrSc = 1+.3*pow(getDestroyFraction(),3.);
	// Not Dead, Normal Size
	else if(destroyShrTimer == -1)
		destShrSc = 1;
	// Shrinking Before Exploding
	else
		destShrSc = 1.3*destroyShrTimer;

	// Shake Character When Dying and Expanding
		float destShPerc = 1 - destroyTimer/DESTROY_TIMER_MAX;
		float destShX, destShY, destShZ;

		if(destroyTimer == -1) {
			destShPerc = 0;
			destShX = 0;
			destShY = 0;
			destShZ = 0;
		}
		else {
			destShX = 5*destShPerc*(rnd()-.5);
			destShY = 5*destShPerc*(rnd()-.5);
			destShZ = 5*destShPerc*(rnd()-.5);
			scZ = 0;
		}

	float dHopZ = hopZ*min(1.f,vel), dHopSc, dHopZVel, dHopX;

	// Calculate Rotation/Positioning Variables w/ Hopping
	if(vel >= 1) {
		dHopSc = hopSc;
		dHopZVel = hopZVel;
		dHopX = hopX;
	}
	else {
		dHopSc = (1-vel) + hopSc*vel;
		dHopZVel = hopZVel*vel;
		dHopX = hopX*vel;
	}

	
	// If PC is Not Slow, Enable Character Shader
	if(!gl->isPCSlow()) {
		gl->enableShader("Character");
		gl->passShaderShadows();
		gl->passShaderLights();
	}
	
	// Set Drawing Color to Character Color
	gl->setColor(255*appearanceR,255*appearanceG,255*appearanceB);

	// Translate Model
	gl->transformTranslation(destShX,destShY,destShZ);
	gl->transformTranslation(x,y,z+dHopZ);
	
	if(onGround) {
		// If on Heightmap, Rotate to Ground
		if(onHeightmap) {
			gl->transformRotationZ(setupRot);	
			gl->transformRotationX(xyRot);
			gl->transformRotationZ(-setupRot);
		}
		
		// Rotate for Shape Direction
		gl->transformRotationZ(faceDir);
		// Rotate for Hopping
		gl->transformRotationX(-dHopX*10);		
		gl->transformRotationY(-dHopZVel*10);		
		gl->transformTranslation(-dHopZVel,dHopX,0);	
	}
	else
		gl->transformRotationZ(faceDir);

	// Scale for Hops
	gl->transformScale(dHopSc,dHopSc,1/dHopSc + scZ);
	// Appearance Scale
	gl->transformScale(appearanceXScale,appearanceYScale,appearanceZScale);

	// Scale Player when Dying
	gl->transformTranslation(0,0,1.*h/2);
	gl->transformScale(destShrSc);
	gl->transformTranslation(0,0,-1.*h/2);

	// Pass Character Direction for Lighting Effect on Model
	gl->setShaderVariable("cDirection", faceDir/180.*3.14159);
	
	// If Dying, Turn Red
	if(destroyTimer > -1)
		gl->setShaderVariable("iHit", destShPerc);
	// If Hurt, Flash Red
	else if(isHurt)
		gl->setShaderVariable("iHit", abs(sin(knockbackTimer)));
	// Otherwise, Normal Color
	else
		gl->setShaderVariable("iHit",0);

	// Pass Model Matrix to Shader (Needed for Shadows!!)
	gl->passModelMatrix();

	// Pass Character Position to Shader
	float charPos[3] = {x,y,z};
	gl->setShaderVec3("charPos", charPos);

	// For Each Shape, Draw Corresponding Shape
	if(shape == SH_PRISM_6)
		gl->draw3DPrism(0,0,0,size,h,6);
	else if(shape == SH_PRISM_5)
		gl->draw3DPrism(0,0,0,size,h,5);
	else if(shape == SH_PRISM_3)
		gl->draw3DPrism(0,0,0,size,h,3);
	else if(shape == SH_CUBE)
		gl->draw3DPrism(0,0,0,size,h,4);
	else if(shape == SH_SPHERE)
		gl->draw3DSphere(0,0,size,size,13);
	else if(shape == SH_CONE_DOWN)
		gl->draw3DCone(0,0,h,size,-h,13);
	else if(shape == SH_CONE_UP)
		gl->draw3DCone(0,0,0,size,h,13);
	else if(shape == SH_CYLINDER)
		gl->draw3DPrism(0,0,0,size,h,13);
	else if(shape == SH_DIAMOND) {
		gl->draw3DFrustem(0,0,0,0,size,h/2,4);
		gl->draw3DFrustem(0,0,h/2,size,0,h/2,4);
	}

	// Clear Transformations
	gl->transformClear();

	// DRAW HELD WEAPON	
		// If PC is Not Slow, Turn on Sword Shader
		if(!gl->isPCSlow()) {
			// Turn on Shader
			gl->enableShader("Blade");
			
			// Pass Shadows, Lights to Shader
			gl->passShaderShadows();
			gl->passShaderLights();

			// Set Light Gray Color
			gl->setColor(200,200,200);
			
			// Pass Character Direction for Sheen of Weapon
			gl->setShaderVariable("cDirection", faceDir/180.*3.14159);
			
			// If Dying, Turn Red
			if(destroyTimer > -1)
				gl->setShaderVariable("iHit", destShPerc);
			// If Hurt, Flash Red
			else if(isHurt)
				gl->setShaderVariable("iHit", abs(sin(knockbackTimer)));
			// Otherwise, No Red
			else
				gl->setShaderVariable("iHit",0);
		}
			// Draw Weapon
			gl->transformTranslation(x,y,z+dHopZ);
		
			if(onGround) {
				// If On Heightmap, Rotate to Ground
				if(onHeightmap) {
					gl->transformRotationZ(setupRot);	
					gl->transformRotationX(xyRot);
					gl->transformRotationZ(-setupRot);
				}

				// Position for Hopping
				gl->transformRotationZ(faceDir);		
				gl->transformTranslation(-dHopZVel,dHopX,0);	
				gl->transformTranslation(-3*dHopZVel,3*dHopX,0);
				gl->transformRotationZ(-faceDir);		
			}
			

			// Rotate to Direction of Weapon
			gl->transformRotationZ(toolDir);
			// If Attacking...
			if(attackTimer != -1)
				// Calculate Timer Percentages for Animation
				float timerPerc = attackTimer/ATTACK_TIMER_MAX;			
					float mTimerPerc = pow(abs(sin(3.14159*(1-timerPerc))),.3);
				float tTimerPerc = min(1.,attackTimer/(ATTACK_TIMER_MAX*.75));
				tTimerPerc = 1.-tTimerPerc;

				// Calculate New Weapon Rotations
				float nXRot, nYRot, nZRot;
				nXRot = mTimerPerc*(20*cos(3.14159*tTimerPerc));
				nYRot = mTimerPerc*(90 + 5*cos(3.14159*tTimerPerc));
				nZRot = mTimerPerc*(180*(-.5 + tTimerPerc));

				float f = 1+2*(1.-mTimerPerc);

				// Calculate Weapon Rotation, Smooth
				wXRot += (nXRot - wXRot)/f;
				wYRot += (nYRot - wYRot)/f;
				wZRot += (nZRot - wZRot)/f;

				// Move Sword in Slashing Motion
				gl->transformRotationZ(wZRot);				
				gl->transformTranslation(7,-6,3);
				gl->transformRotationY(wYRot);
				gl->transformRotationX(wXRot);
				gl->transformTranslation(-7,6,-3);

			}

			// Translate Weapon to Player's Hand
			gl->transformTranslation(7,-6,3 + upZ);

			// Scale Weapon to Make it Slightly Longer (and Stretch when Hurt!)
			gl->transformScale(1,1,1.3+scZ);
			// Shrink Weapon if Dying
			gl->transformScale(destShrSc);

			//Pass Direction of Weapon (Used for Calculating Lighting)
			gl->setShaderVariable("cDirection", toolDir/180.*3.14159);
			
			// If Hurt, Change Color to Red
			if(isHurt)
				gl->setShaderVariable("iHit", abs(sin(knockbackTimer)));
			else
				gl->setShaderVariable("iHit",0);


			// Pass Model Matrix to Shader
			gl->passModelMatrix();
			
			// Draw Hilt
			gl->draw3DPrism(0,0,.5,.5,2,3,swordHiltTex);
			gl->draw3DBlock(-.8,-2,2,.8,2,3,swordHiltTex);

			// Draw Blade
			gl->draw3DCone(0,0,7,1,3,3);
			gl->draw3DFrustem(0,0,2,.8,1,5,3);

	// Return Transformation to Normal
	gl->transformClear();

	// Disable Shaders, Return Color to White
	gl->disableShaders();
	gl->setColor(255,255,255);
}

// Draw Stats Window
void Character :: drawStatWindow(GraphicsOGL* gl, float perc) {

	// Determine Starting Position
	float oX, oY, dX, dY, w = 200, h = 200;
	dX = oX = 640-w*perc;
	dY = oY = 480-h;
	dX += 16;
	dY += 16;

	string diff, shp;

	// Get Skill Rank as Text
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
	
	// Get Shape Text
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
		case SH_DIAMOND:
			shp = "Diamond"; break;
	}
	
	// Draw Name
	gl->setColor(255,255,255);
	gl->drawString(dX,dY,"  " + diff + " " + shp);
		dY += 25;


	// Get Stats as Integers, to Prevent Decimal Points
	int at, de, he, mHe;
	at = atk;	
	de = def;
	he = hp;
	mHe = maxHP;

	// Print Stats
	// Level
	gl->drawString(dX,dY,"Lvl: " + to_string(level));
		dY += 15;
	// Attack
	gl->drawString(dX,dY,"Atk: " + to_string(at));
		dX += w/2-16;
	// Defense
	gl->drawString(dX,dY,"Def: " + to_string(de));
		dX = oX+16;
		dY += 15;
	// HP Fraction
	gl->drawString(dX,dY,"HP: " + to_string(he) + " / " + to_string(mHe));
		dY += 15;
	// Draw Health Bar
	gl->drawHealth(dX,dY,he,mHe);
		dY += 15;
	
	// Draw Outline
	gl->setColor(20,20,20);
	gl->drawRect(oX,oY,oX+w,oY+h);
	gl->setColor(180,180,180);
	gl->drawRect(oX+1,oY+1,oX+w-1,oY+h-1);

	// Draw Background
	gl->setColor(20,20,20,200);
	gl->fillRect(oX,oY,oX+w,oY+h);
}


// Smoothly Rotate Shape
void Character :: faceDirection(float dir) {
	faceDir += calcTurnToDir(faceDir,dir);
}
// Rotate Weapon
void Character :: toolDirection(float dir) {
	toolDir = dir;
}

// Knockback w/ Direction
void Character :: knockback(float kDir) {
	knockback(1,kDir);
}

// Knockback w/ Fraction, Direction
void Character :: knockback(float f, float kDir) {

	// If not Knocked Back At the Moment
	if(knockbackTimer == -1) {
		// Set Knockback Direction, Timer
		knockbackDir = kDir;
		knockbackTimer = f*KNOCKBACK_TIMER_MAX;

		// Set Z Velocity
		zVel = f*1.5;
	}
}

// Calculate Damage
float Character :: calcDamage(float attackPower, Character* attacker, Character* defender) {
	
	// (Formula from Pokemon)
	float modifier = 1.*1*1*1*(.85 + .15*rnd());
	return ((2.*attacker->level + 10)/250*(attacker->atk/defender->def)*attackPower + 2)*modifier;
}



// PRIVATE FUNCTIONS
	void Character :: updateHop(GraphicsOGL* gl, float deltaT) {
		float hopZVelP = hopZVel;
		float chAmt = 10;

		// If On Ground, Hop
		if(onGround) {
			// Accelerate and Apply Velocity
			hopZVel += GRAVITY_HOP_ACCELERATION;
			hopZ += hopZVel;
			
			// If Hit Ground, 
			if(hopZ <= 0) {
				// If REALLY Just Landing on Ground
				if(hopZVel != GRAVITY_HOP_ACCELERATION) {
					// Create Smoke Ring, Play Footstep Sound
					new SmokeRing(x,y,z,2,8,4,1.3*min(1.f,vel));
					SoundController::playSound("fsGrass",this);
				}

				// Set Z and Vel to 0
				hopZ = hopZVel = 0;

				// Increase Scale of Player
				if(hopZVelP != 0)
					hopSc *= 1.3;
			}

			// Return Scale to 1
			hopSc += (1 - hopSc)/3;

			// Move Character Back and Forth
			if(isMoving)
				hopX += ((2*hopDir*(hopHeight-hopZ)/hopHeight) - hopX)/chAmt;
		}
		// Otherwise, Unhop
		else {
			hopZ = 0;
			hopZVel = 0;
			hopSc += (1 - hopSc)/3;
		}

		// If Not Moving or In Air, Move Player to Center
		if(!isMoving || !onGround)
			hopX += (0 - hopX)/chAmt;
	}

	// Perform Hop
	void Character :: hop() {
		// If "On Ground" in Terms of Hopping
		if(hopZ == 0) {
			// If Moving Slowly, Perform Normal Hops
			if(vel <= 1)
				hopZVel = (.75 + .25*vel)*hopSpeed*(1. + .1*(rnd()-.5));
			// If Running, Perform Fast Hops
			else
				hopZVel = (1 - .25/3*vel)*hopSpeed*(1. + .1*(rnd()-.5));

			// Negate Hopping Direction (To Hop Left and Right)
			hopDir *= -1;
		}
	}

	// Landing on Ground
	void Character :: land() {

		// Squish Character
		hopSc *= 2;
		// Create Smoke Ring
		new SmokeRing(x,y,z,4,13,7,2);
		// Play Grass Sound
		SoundController::playSound("fsGrass");
	}



// ACCESSOR/MUTATOR
	float Character :: getSize() {
		return size;
	}

	float Character :: getHP() {
		return hp;
	}

	float Character :: getMaxHP() {
		return maxHP;
	}

	// Get Destroy Animation Progress as Fraction	
	float Character :: getDestroyFraction() {
		if(destroyTimer == -1)
			return -1;
		else if(destroyTimer > -1)
			return 1 - destroyTimer/DESTROY_TIMER_MAX;
		else
			return destroyShrTimer;
	}

	// Get Target
	Character* Character :: getTarget() {
		return target;
	}

	// Get Target Window Fraction Onscreen
	float Character :: getTargetShift() {
		return targetShift;
	}