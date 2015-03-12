// Tree.h


#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"

class Tree : public Physical {
	public:
		Tree(int,int,int);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		void land();

		Branch* root;
};

#endif
