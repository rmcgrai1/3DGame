// Lamp.h


#ifndef LAMP_H
#define LAMP_H

#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"


class Lamp : public Physical {
	public:
		Lamp(float,float,float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		float height;
		float rotate;
};

#endif
