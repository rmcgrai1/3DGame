// Tree.cpp
// Ryan McGrail

#include "../Sound/SoundController.h"
#include "../Graphics/TextureController.h"
#include "Tree.h"
#include "Branch.h"
#include <stdlib.h>
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include <cmath>

SortedList<Tree*> Tree :: treeList;

// Constructor
Tree :: Tree(float x, float y, float newSize) : Environmental(x,y) {

	// Initialize Health
	health = 3;

	// Enable Growing, Shadows
	isGrowing = true;
	hasShadow = true;

	root = NULL;	//root = new Branch(0,5, 15., 0, 90);

	// Size Vars
	size = .05;
	toSize = newSize;

	// Falling Vars
	fallXYDir = 0;
	fallZDir = 0;
	fallZVel = 0;


	damageShakeTimer = -1;
	growWobble = .25;

	branchTex = TextureController::getTexture("pineBranch");
	barkTex = TextureController::getTexture("bark");

	treeList.add(this);
}

// Destroying Tree
void Tree :: destroy() {
	Environmental :: destroy();

	treeList.destroy(this);
}

// Applying Damage, Changing Falling Direction
void Tree :: damage(float newDir) {
	// If Not Already Damaged, Start Shaking Animation
	if(damageShakeTimer == -1) {
		SoundController :: playSound("treeDamage",this);
		fallXYDir = newDir;
		damageShakeTimer = 10;
		health--;
	}
}

// Getting Size of Tree
float Tree :: getSize() {
	return size;
}

// Getting if Tree has a Shadow
bool Tree :: getHasShadow() {
	return hasShadow;
}

// Updating
void Tree :: update(GraphicsOGL* gl, float deltaTime) {
	Environmental :: update(gl, deltaTime);

	// If Damaged, Shake
	if(damageShakeTimer > -1) {
		damageShakeTimer -= deltaTime;

		// If Less than -1, Stop Shaking
		if(damageShakeTimer <= -1) {
			damageShakeTimer = -1;

			// If Dead, Start Dying Animation
			if(health <= 0) {
				SoundController :: playSound("treeDie",this);
				damageShakeTimer = -2;
			}
		}
	}
	
	// Death Animation
	if(health <= 0 && damageShakeTimer == -2) {
		// If Falling, and Not Done Falling, Bounce
		if(fallZVel != 10000) {
			// Accelerate Falling Speed & Rotate
			fallZVel += .0625;
			fallZDir += fallZVel;

			// If Rotated All Way to Ground, Bounce or Stop Bouncing
			if(fallZDir >= 90) {
				// Play Sound as Hitting Ground
				SoundController :: playSound("heavyFall",this);
				
				// Bounce
				fallZDir = 90;
				fallZVel *= -.25;

				// If Falling Velocity Small, Stop Falling
				if(abs(fallZVel) < .05)
					fallZVel = 10000;
			}
		}
		// Otherwise, Done Falling & Bouncing, Shrink
		else {
			fallZDir = 90;
			toSize = 0;
		}

		// If Too Small, Destroy
		if(size < .01) {
			destroy();
		}
	}

	// If Growing, Increase in Size
	if(isGrowing) {
		// Increase Size Smoothly
		size += (growWobble > 0 ? 1 : -1)*abs(toSize+growWobble - ((toSize+growWobble) - size))/10;

		// If Past Size, Reverse Wobble Direction
		if((growWobble > 0 && size > toSize+growWobble) || (growWobble < 0 && size < toSize+growWobble)) {
			growWobble *= -.5;
		}
		// If Wobble Amount Small, Stop Wobbling
		else if(abs(growWobble) < .01)
			isGrowing = false;
	}
	else
		size += (toSize - size)/10;
}

// Drawing Tree, Branches
void Tree :: draw(GraphicsOGL* gl, float deltaTime) {
	root->draw(gl, x,y,z);
}
