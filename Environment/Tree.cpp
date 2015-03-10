// Tree.cpp


#include "Tree.h"
#include "Branch.h"
#include <stdlib.h>
#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"

Tree :: Tree(int x, int y, int z) : Physical(x,y,z) {
	root = new Branch(0,5, 15., 0, 90);	
}

void Tree :: update(GraphicsOGL* gl, float deltaTime) {
}
void Tree :: draw(GraphicsOGL* gl, float deltaTime) {
	root->draw(gl, x,y,z);
}

void Tree :: land() {
}
