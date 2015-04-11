// DeathPuff.h

#ifndef DEATHPUFF_H
#define DEATHPUFF_H

#include "../Graphics/GraphicsOGL.h"
#include "Particle.h"

class DeathPuff : public Particle {
	public:
		DeathPuff(float,float,float,float,float,float,float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		float toX;
		float toY;
		float toZ;
		float toPerc;
		float rad;
		float percDiv
};

#endif