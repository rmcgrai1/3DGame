// Lamp.h
// Ryan McGrail

#ifndef LAMP_H
#define LAMP_H

#include <vector>
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"


class Lamp : public Environmental {
	public:
		Lamp(float,float);							// Constructors
		Lamp(float,float,float);
		Lamp(float,float,float,float,float,float);
		void update(GraphicsOGL*, float);			// Updating
		void draw(GraphicsOGL*, float);				// Drawing
		void damage(float);							// Damaging Lights

		float getLightX();							// Get Light Position
		float getLightY();
		float getLightZ();
		float getLightR();							// Get Light Color
		float getLightG();
		float getLightB();
		float getLightA();
		float getLightRadius();						// Get Light Radius

		static vector<Lamp*> lampList;				// List of Lights

	private:
		float rotate;								// Rotation of Lantern

		float lightX;								// Light Position
		float lightY;
		float lightZ;
		float rad;									// Light Radius

		float R;									// Color
		float G;
		float B;
		float A;

		float xydir;								// Rotation
		float lightTimer;							// Light Timer for Flickering
};

#endif
