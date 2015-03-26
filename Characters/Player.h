// Player.h


#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"

class Player : public Character {
	public:
		Player(float, float, float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	protected:
		void land();

	private:
		void updateControl(GraphicsOGL*, float);

		float camDis;
		int flight;
};

#endif
