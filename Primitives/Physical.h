// Physical.h


#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "../Environment/Heightmap.h"

class GraphicsOGL;
class Physical : public Instantiable {
	public:
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

		void setZ(float);

		//COLLISION
		bool collideHeightmap(Heightmap*);

	private:
		void updateMotion(float);

	protected:
		Physical(float, float, float);
		float x;
		float y;
		float z;
		float xP;
		float yP;
		float zP;
		float vel;
		float direction;			
};

#endif
