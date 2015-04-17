// NPC.h


#ifndef ANIMAL_H
#define ANIMAL_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"

class Animal : public Character {
	public:
		Animal(float, float, float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);


	private:
		void updateControl(GraphicsOGL*, float);
		void land();
};

#endif
