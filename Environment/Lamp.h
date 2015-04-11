// Lamp.h


#ifndef LAMP_H
#define LAMP_H

#include <vector>
#include "Environmental.h"
#include "../Graphics/GraphicsOGL.h"


class Lamp : public Environmental {
	public:
		Lamp(float,float);
		Lamp(float,float,float);
		Lamp(float,float,float,float,float,float);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
		void damage(float);

		float getLightX();
		float getLightY();
		float getLightZ();
		float getLightR();
		float getLightG();
		float getLightB();
		float getLightA();
		float getLightRadius();

		static vector<Lamp*> lampList;

	private:
		float height;
		float rotate;

		float lightX;
		float lightY;
		float lightZ;
		float rad;

		float R;
		float G;
		float B;
		float A;

		float xydir;
		float lightTimer;
};

#endif
