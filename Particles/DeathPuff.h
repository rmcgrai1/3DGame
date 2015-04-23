// DeathPuff.h
// Ryan McGrail

// (These are the puffs that appear when a character dies.)

#ifndef DEATHPUFF_H
#define DEATHPUFF_H

#include "../Graphics/GraphicsOGL.h"
#include "Particle.h"

class DeathPuff : public Particle {
	public:
		DeathPuff(float,float,float,float,float,float,float,float);		// Constructor
		void update(GraphicsOGL*, float);								// Update Function
		void draw(GraphicsOGL*, float);									// Draw Function

	private:
		float toX;														// Direction Normal X
		float toY;														// Direction Normal Y
		float toZ;														// Direction Normal Z
		float toPerc;													// Percentage btwn 0 and 1 Along Line from Starting Position to End Position
		float puffSize;													// Puff Size
		float percDiv;													// "Velocity" of Travel (Quotes because, in Reality, Smaller Means Faster)
};

#endif
