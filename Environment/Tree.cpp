// Tree.cpp


#include "Tree.h"
#include "Branch.h"
#include <stdlib.h>
#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"

Tree :: Tree(float x, float y, float z, float newSize) : Physical(x,y,z) {

	root = new Branch(0,5, 15., 0, 90);
	size = newSize;
}

void Tree :: update(GraphicsOGL* gl, float deltaTime) {
	Physical :: update(gl, deltaTime);
}
void Tree :: draw(GraphicsOGL* gl, float deltaTime) {
	root->draw(gl, x,y,z);
}

void Tree :: land() {
}
