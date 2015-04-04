// Physical.h

// The Physical class is used for any object that will undergo basic physics. It can collide with other objects,
// and will automatically travel based on its xy- and z- velocity and direction. Not everything that can collide
// derives from Physical; only those that should be able to move. Trees, for instance, stay still, so they are
// not of type Physical.


#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Instantiable.h"
#include "../Environment/Heightmap.h"


class GraphicsOGL;
class Physical : public Instantiable {

	public:
								// PARENT FUNCTIONS
		virtual void update(GraphicsOGL*, float);		// Update Function
		virtual void draw(GraphicsOGL*, float);			// Draw Function
		virtual void destroy();
								// ACCESSOR/MUTATOR FUNCTIONS
		void setX(float);					// Set X
		void setY(float);					// Set Y
		void setZ(float);					// Set Z
		float getX();						// Get X
		float getY();						// Get Y
		float getZ();						// Get Z

								// CONSTANTS
		static const float GRAVITY_ACCELERATION;		// Acceleration due to Gravity

	private:
								// UPDATE FUNCTIONS
		void updateMotion(float);				// Update Physical Motion

								// COLLISION FUNCTIONS
		bool collideHeightmap(Heightmap*);			// Collide with Heightmap

								// VIRTUAL FUNCTIONS
		virtual void land() = 0;				// What Happens when Landing


	protected:
								// CONSTRUCTOR(S)
		Physical(float, float, float);				// Position Constructor
		




								// VARIABLES
		float x;						// X Coordinate
		float y;						// Y Coordinate
		float z;						// Z Coordinate
		float xP;						// Previous X Coordinate
		float yP;						// Previous Y Coordinate
		float zP;						// Previous Z Coordinate
		float vel;						// XY Velocity
		float zVel;						// Z Velocity
		float direction;					// Direction
		float floorZ;

		bool onGround;
};

#endif
