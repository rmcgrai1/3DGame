// Environmental.h

#ifndef ENVIRONMENTAL_H
#define ENVIRONMENTAL_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Instantiable.h"

class Environmental : public Instantiable {

	public:
		Environmental(float,float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

		float getX();
		float getY();
		float getZ();

	protected:
		float x;
		float y;
		float z;

	private:
		void placeOnGround(GraphicsOGL*);
		bool onGround;
};

#endif
