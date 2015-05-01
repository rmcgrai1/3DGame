// DirtPath.h
// Ryan McGrail

#ifndef DIRTPATH_H
#define DIRTPATH_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class DirtPath : public Drawable2 {
	public:	
		DirtPath();									// Constructor
		void draw(GraphicsOGL*, float);				// Drawing
		void update(GraphicsOGL*, float);			// Updating
		float pts[300];								// Path Points
		int numPts;									// # of Path Points (Max is 100)

		void addPt(float,float,float);				// Adding Path Point
};

#endif
