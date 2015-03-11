// Player.h


#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "../Characters/Character.h"
#include "../Graphics/Texture.h"
#include "../Controller.h"

class Player : public Character {
	public:
		Player(float, float, float);
		void update(Controller*, float);
		void draw(Controller*, float);


	private:
		void updateControl(Controller*, float);
		void land();
};

#endif
