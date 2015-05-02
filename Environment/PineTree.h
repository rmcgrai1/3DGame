// PineTree.h
// Ryan McGrail

#ifndef PINETREE_H
#define PINETREE_H

#include "../Graphics/GraphicsOGL.h"
#include "Tree.h"

class PineTree : public Tree {
	public:
		PineTree(float, float,float,float,float,float);		// Constructor
		void update(GraphicsOGL*, float);					// Updating
		void draw(GraphicsOGL*, float);						// Drawing

	private:
		float colRed;										// Color
		float colGreen;
		float colBlue;
};

#endif
