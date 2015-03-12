// Water.h

#ifndef WATER_H
#define WATER_H


#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class Water : public Drawable2 {
	public:
		Water(float, float, float);

		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

		float getSeaLevel();

	private:
		float width;
		float height;
		float seaLevel;
};

#endif
