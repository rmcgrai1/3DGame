// Tree.h


#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"

class Tree : public Environmental {
	public:
		Tree(float,float,float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

	protected:
		Branch* root;
		float size;
		float toSize;

		bool isGrowing;
		float growWobble;
};

#endif
