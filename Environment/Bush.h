// Bush.h
// Ryan McGrail

#ifndef BUSH_H
#define BUSH_H

#include "../Graphics/GraphicsOGL.h"
#include "Tree.h"

class Bush : public Tree {
	public:
		Bush(float, float,float,float,float,float);		// Constructor
		void update(GraphicsOGL*, float);				// Updating
		void draw(GraphicsOGL*, float);					// Drawing

	private:
		float colRed;									// Colors
		float colGreen;
		float colBlue;
};

#endif
