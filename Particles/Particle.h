// Particle.h
// Ryan McGrail


#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Instantiable.h"

class Particle : public Instantiable {
	public:
		virtual void update(GraphicsOGL*, float);	// Updating
		virtual void draw(GraphicsOGL*, float);		// Drawing

	protected:
		Particle(float,float,float);				// Protected Constructor
		
		float x;									// X
		float y;									// Y
		float z;									// Z
};

#endif
