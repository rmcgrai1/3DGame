// Environmental.h

#ifndef ENVIRONMENTAL_H
#define ENVIRONMENTAL_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Instantiable.h"

class Environmental : public Instantiable {

	public:
		Environmental(float,float);
		Environmental(float,float,float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		virtual void damage(float) = 0;
		virtual bool checkOnScreen(GraphicsOGL*);

		float getX();
		float getY();
		float getZ();

	protected:
		float x;
		float y;
		float z;

		float health;

	private:
		void placeOnGround(GraphicsOGL*);
		bool onGround;
};

#endif
