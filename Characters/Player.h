// Player.h


#ifndef PLAYER_H
#define PLAYER_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"

class GraphicsOGL;
class Player : public Physical {
	public:
		Player(float, float, float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);

	private:
		void updateControl(GraphicsOGL*, float);

		float hopZ;
		float hopZVel;
		float hopSc;
};

#endif
