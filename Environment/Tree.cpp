// Tree.cpp


#include "Tree.h"
#include "Branch.h"
#include <stdlib.h>
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"
#include <cmath>


SortedList<Tree*> Tree :: treeList;

Tree :: Tree(float x, float y, float newSize) : Environmental(x,y) {

	isGrowing = true;

	root = new Branch(0,5, 15., 0, 90);
	size = .05;
	toSize = newSize;

	growWobble = .25;

	treeList.add(this);
}

float Tree :: getSize() {
	return size;
}

void Tree :: update(GraphicsOGL* gl, float deltaTime) {
	Environmental :: update(gl, deltaTime);

	if(isGrowing) {
		size += (growWobble > 0 ? 1 : -1)*abs(toSize+growWobble - ((toSize+growWobble) - size))/10;

		if((growWobble > 0 && size > toSize+growWobble) || (growWobble < 0 && size < toSize+growWobble)) {
			growWobble *= -.5;
		}
		else if(abs(growWobble) < .01)
			isGrowing = false;
	}
	else {
		size += (toSize - size)/10;
	}
}
void Tree :: draw(GraphicsOGL* gl, float deltaTime) {
	root->draw(gl, x,y,z);
}
