// NPC.cpp
// Ryan McGrail

#include <deque>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <string>
#include <iostream>
#include "../IO/InputController.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "Character.h"
#include "NPC.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;

#define MODE_CHASE 1
#define MODE_ATTACK 2
#define MODE_ROAM 0


// Constructor
NPC :: NPC(float x, float y, float z) : Character(x,y,z) {
}	

// Update Character
void NPC :: update(GraphicsOGL* gl, float deltaTime) {

	// Inherited Update Code
	Character :: update(gl, deltaTime);

	// Update Control of NPC
	updateControl(gl,deltaTime);
}

// Drawing NPC
void NPC :: draw(GraphicsOGL* gl, float deltaTime) {

	// Draw NPC
	Character :: draw(gl, deltaTime);
}

// Update Control (AI)
void NPC :: updateControl(GraphicsOGL* gl, float deltaTime) {
	InputController* i = gl->getInputController();

	int mode;

	// Get Direction to Player
	Character* p = gl->getPlayer();
	float toPlayerDir;
	toPlayerDir = calcPtDir(x,y,p->getX(),p->getY());

	// If Far from Player or Can't See Player, Roam
	if(calcPtDis(x,y,p->getX(),p->getY()) > 150 || abs(calcAngleDiff(toPlayerDir,faceDir)) > 50)
		mode = MODE_ROAM;
	// If Near Player, Chase
	else if(calcPtDis(x,y,p->getX(),p->getY()) > p->getSize()+size+3)
		mode = MODE_CHASE;
	// If Next to Player, Attack
	else
		mode = MODE_ATTACK;

	
	// If Far from Player, Roam
	if(mode == MODE_ROAM) {
		// Face Player
		float dir = 5*rnd(-1,1);
		direction += dir;
		faceDirection(direction);
		toolDirection(direction);

		// Move Slow
		isMoving = true;
		vel = 1;
	}
	// If Close, Chase
	else if(mode == MODE_CHASE) {
	
		// Face towards Player
		float dir = toPlayerDir;
		direction += calcTurnToDir(direction, dir);
		faceDirection(direction);
		toolDirection(direction);

		// Move Fast
		isMoving = true;
		vel = 2;
	}
	// If Close Enough, Attack!
	else if(mode == MODE_ATTACK) {
		float dir = toPlayerDir;

		// Face Weapon Towards Player
		toolDirection(direction);
		// Attack
		attack();
	}

	// Hop While Moving
	hop();
}

// Landing Code
void NPC :: land() {
}
