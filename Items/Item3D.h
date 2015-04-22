// Item3D.h


#ifndef ITEM3D_H
#define ITEM3D_H

#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
using namespace std;

class Item3D : public Physical {
	public:
		~Item3D();
		Item3D(int, string, string);
		
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		virtual Item3D* instantiate(float, float, float);

		static int TYPE_POTION;
		
	protected:
		Item3D(float, float, float);
		void land();

		int type;
		string* name;
		string* description;
};

#endif
