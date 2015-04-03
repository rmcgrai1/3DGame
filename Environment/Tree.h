// Tree.h


#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"

class Tree : public Physical {
	public:
		Tree(float,float,float,float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

	protected:
		void land();

		Branch* root;
		float size;
};

#endif
