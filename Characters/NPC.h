// NPC.h


#ifndef NPC_H
#define NPC_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"

class NPC : public Character {
	public:
		NPC(float, float, float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);


	protected:
		void land();
};

#endif
