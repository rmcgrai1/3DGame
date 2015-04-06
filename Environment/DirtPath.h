// DirtPath.h

#ifndef DIRTPATH_H
#define DIRTPATH_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class DirtPath : public Drawable2 {
	public:	
		DirtPath();
		void draw(GraphicsOGL*, float);
		void update(GraphicsOGL*, float);
		float pts[300];
		int numPts;

		void addPt(float,float,float);
};

#endif
