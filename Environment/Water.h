// Water.h
// Ryan McGrail

#ifndef WATER_H
#define WATER_H


#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class Water : public Drawable2 {
	public:
		Water(float, float, float);				// Constructor

		void update(GraphicsOGL*, float);		// Updating
		void draw(GraphicsOGL*, float);			// Drawing

		float getSeaLevel();					// Getting Sea Level Height

	private:
		float width;							// Width of Water (X)
		float height;							// Height of Water (Y)
		float seaLevel;							// Sea Level Height (Z)
};

#endif
