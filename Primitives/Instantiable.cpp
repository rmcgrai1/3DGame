// Instantiable.cpp


#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"
#include "Instantiable.h"


deque<Instantiable*> Instantiable :: instanceList;
deque<Instantiable*> Instantiable :: removeIList;


Instantiable :: Instantiable() : Drawable2() {
	instanceList.push_back(this);
}

void Instantiable :: update(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Update Function
	Drawable2 :: update(gl, deltaTime);
}

void Instantiable :: draw(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Draw Function
	Drawable2 :: draw(gl, deltaTime);
}

void Instantiable :: destroy() {
	Drawable2 :: destroy();

	removeIList.push_back(this);
}

void Instantiable :: removeDestroyed() {
	Instantiable* inst;

	for(int i = 0; i < removeIList.size(); i++) {
		inst = removeIList[i];

		for(int j = 0; j < instanceList.size(); j++)
			if(instanceList[j] == inst) {
				instanceList.erase(instanceList.begin()+j);
				break;
			}
	}

	removeIList.clear();
}

