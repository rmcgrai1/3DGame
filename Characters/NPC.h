// NPC.h
// Ryan McGrail

#ifndef NPC_H
#define NPC_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"

class NPC : public Character {
	public:
		NPC(float, float, float);						// Constructor
		void update(GraphicsOGL*, float);				// Updating
		void draw(GraphicsOGL*, float);					// Drawing

	private:
		void updateControl(GraphicsOGL*, float);		// Updating Control of NPC
		void land();									// Landing on Ground
};

#endif
