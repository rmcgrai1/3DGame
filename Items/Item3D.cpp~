// Item3D.cpp


#include "Item3D.h"
#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
using namespace std;

int Item3D :: TYPE_POTION = 0;


Item3D :: Item3D(int newType, string newName, string newDesc) : Physical(0,0,0) {
	doUpdates = false;
	visible = false;

	type = newType;
	name = &newName;
	description = &newDesc;
}

Item3D :: ~Item3D() {
}

Item3D :: Item3D(float nX, float nY, float nZ) : Physical(nX, nY, nZ) {
}

void Item3D :: land(GraphicsOGL* gl) {
}

void Item3D :: update(GraphicsOGL* gl, float deltaTime) {
	Physical :: update(gl, deltaTime);
}

void Item3D :: draw(GraphicsOGL* gl, float deltaTime) {
	
	gl->transformClear();
	gl->transformTranslation(x, y, z);

	if(type == TYPE_POTION) {
		gl->draw3DFrustem(0,0,0,1,4,2, 5);
		gl->draw3DFrustem(0,0,2,4,1,2, 5);
		gl->draw3DFrustem(0,0,4,1,1.3,4, 5);
	}

	gl->transformClear();
}

Item3D* Item3D :: instantiate(float nX, float nY, float nZ) {

	Item3D* it = new Item3D(nX, nY, nZ);
	it->type = type;
	it->name = name;
	it->description = description;

	return it;
}
