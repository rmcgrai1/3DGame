// AttackSwing.h
// Ryan McGrail

// NEVER COMPLETED

#ifndef ATTACKSWING_H
#define ATTACKSWING_H

#include "../Graphics/GraphicsOGL.h"
#include "Particle.h"

class AttacSwing : public Particle {
	public:
		AttackSwing(float x, float y, float z, float dir);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		float alpha;
		float dir;
};

#endif
