// Tree.h
// Ryan McGrail

#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Data/SortedList.h"
#include "../Graphics/Texture.h"

class Tree : public Environmental {
	public:
		Tree(float,float,float);						// Constructor
		virtual void update(GraphicsOGL*, float);		// Updating
		virtual void draw(GraphicsOGL*, float);			// Drawing
		void destroy();									// Destroying Object
		void damage(float);								// Applying Damage, Updating Falling Direction

		static SortedList<Tree*> treeList;				// List of Trees

		float getSize();								// Size of Tree
		bool getHasShadow();							// Check if Tree Has Shadow

	protected:
		Branch* root;									// Root Branch
		float size;										// Current Size
		float toSize;									// To Size

		bool hasShadow;									// Does Tree have Shadow?

		bool isGrowing;									// Growing Vars
		float growWobble;

		float fallXYDir;								// Falling Vars
		float fallZDir;
		float fallZVel;

		Texture* branchTex;								// Branch Texture
		Texture* barkTex;								// Bark Texture

		float damageShakeTimer;							// Timer for Shaking Animation
};

#endif
