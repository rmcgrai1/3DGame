// Environmental.h
// Ryan McGrail

#ifndef ENVIRONMENTAL_H
#define ENVIRONMENTAL_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Instantiable.h"

class Environmental : public Instantiable {

	public:
		Environmental(float,float);						// Constructor, XY
		Environmental(float,float,float);				// Constructor, XYZ
		virtual void update(GraphicsOGL*, float);		// Updating
		virtual void draw(GraphicsOGL*, float);			// Drawing
		virtual void damage(float) = 0;					// Damaging Environmental Object
		virtual bool checkOnScreen(GraphicsOGL*);		// Checking if Onscreen

		float getX();									// Getting Position
		float getY();
		float getZ();

	protected:
		float x;										// Position
		float y;
		float z;

		float health;									// Health

	private:
		void placeOnGround(GraphicsOGL*);				// Placing on Ground
		bool onGround;									// Has Been Placed?
};

#endif
