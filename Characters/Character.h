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
<<<<<<< HEAD
		float faceDir;
		bool isMoving;
=======
		float hopZ;
		float hopZVel;
>>>>>>> 6e6d2a149e943776a9a8f1acf981155ac29b65ba

	private:
		void updateHop(float);
		
<<<<<<< HEAD
		float hopX;
		float hopZ;
		float hopZVel;
=======
		bool isMoving;
>>>>>>> 6e6d2a149e943776a9a8f1acf981155ac29b65ba
		float hopSc;
		float hopDir;
		
		static Texture* shTex;
};

#endif
