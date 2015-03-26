// Character.h


#ifndef CHARACTER_H
#define CHARACTER_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "../Graphics/Texture.h"

class GraphicsOGL;
class Character : public Physical {
	public:
		Character(float, float, float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		void faceDirection(float);

		static float GRAVITY_HOP_ACCELERATION;

	protected:
		virtual void land();
		void hop();
		float faceDir;
		bool isMoving;

	private:
		void updateHop(float);
		
		float hopX;
		float hopZ;
		float hopZVel;
		float hopSc;
		float hopDir;
		
		static Texture* shTex;
};

#endif
