// Player.h
// Ryan McGrail

#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"

class Player : public Character {
	public:
		Player(float, float, float);					// Constructor
		void update(GraphicsOGL*, float);				// Updating
		void draw(GraphicsOGL*, float);					// Drawing
		
	private:
		void updateControl(GraphicsOGL*, float);		// Updating Controls
		float camDis;									// Camera's Distance from Player
		float camDir;									// Camera Direction to Player
};

#endif
