// Tree.cpp


#include "../Sound/SoundController.h"
#include "Tree.h"
#include "Branch.h"
#include <stdlib.h>
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include <cmath>

SortedList<Tree*> Tree :: treeList;

Tree :: Tree(float x, float y, float newSize) : Environmental(x,y) {

	health = 3;

	isGrowing = true;
	hasShadow = true;

	root = NULL;
	//root = new Branch(0,5, 15., 0, 90);
	size = .05;
	toSize = newSize;

	fallXYDir = 0;
	fallZDir = 0;
	fallZVel = 0;


	damageShakeTimer = -1;
	growWobble = .25;

	treeList.add(this);
}

void Tree :: destroy() {
	Environmental :: destroy();

	treeList.destroy(this);
}

void Tree :: damage(float newDir) {
	if(damageShakeTimer == -1) {
		SoundController :: playSound("treeDamage",this);
		fallXYDir = newDir;
		damageShakeTimer = 10;
		health--;
	}
}

float Tree :: getSize() {
	return size;
}

bool Tree :: getHasShadow() {
	return hasShadow;
}

void Tree :: update(GraphicsOGL* gl, float deltaTime) {
	Environmental :: update(gl, deltaTime);

	if(damageShakeTimer > -1) {
		damageShakeTimer -= deltaTime;

		if(damageShakeTimer <= -1) {
			damageShakeTimer = -1;

			if(health <= 0) {
				SoundController :: playSound("treeDie",this);
				damageShakeTimer = -2;
			}
		}
	}
	if(health <= 0 && damageShakeTimer == -2) {
		if(fallZVel != 10000) {
			fallZVel += .0625;
			fallZDir += fallZVel;

			if(fallZDir >= 90) {
				SoundController :: playSound("heavyFall",this);
				fallZDir = 90;
				fallZVel *= -.25;

				if(abs(fallZVel) < .05)
					fallZVel = 10000;
			}
			//fallZDir += (90 - (90 - fallZDir))/30.;
		}
		else {
			fallZDir = 90;
			toSize = 0;
		}

		if(size < .01) {
			destroy();
		}
	}


	if(isGrowing) {
		size += (growWobble > 0 ? 1 : -1)*abs(toSize+growWobble - ((toSize+growWobble) - size))/10;

		if((growWobble > 0 && size > toSize+growWobble) || (growWobble < 0 && size < toSize+growWobble)) {
			growWobble *= -.5;
		}
		else if(abs(growWobble) < .01)
			isGrowing = false;
	}
	else
		size += (toSize - size)/10;
}
void Tree :: draw(GraphicsOGL* gl, float deltaTime) {
	root->draw(gl, x,y,z);
}
