// PineTree.h

#ifndef PINETREE_H
#define PINETREE_H

#include "../Graphics/GraphicsOGL.h"
#include "Tree.h"

class PineTree : public Tree {
	public:
		PineTree(float, float, float,float,float,float,float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		float colRed;
		float colGreen;
		float colBlue;
};

#endif
