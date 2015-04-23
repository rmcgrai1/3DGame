// SmokeRing.h
// Ryan McGrail

#ifndef SMOKERING_H
#define SMOKERING_H

#include "../Graphics/GraphicsOGL.h"
#include "Particle.h"

class SmokeRing : public Particle {
	public:
		SmokeRing(float,float,float,float,float,int,float);		// Constructor
		void update(GraphicsOGL*, float);						// Updating
		void draw(GraphicsOGL*, float);							// Drawing

	private:
		float startSize;										// Starting Radius
		float endSize;											// End Radius
		float curSize;											// Current Radius
		float percDiv;											// "Velocity" of Animation (Slower = Faster)
		float percSmoke;										// Animation/Alpha
		float alpha;											// Transparency
};

#endif
