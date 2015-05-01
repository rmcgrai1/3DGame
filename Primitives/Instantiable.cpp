// Instantiable.cpp
/// Ryan McGrail

#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"
#include "Instantiable.h"


deque<Instantiable*> Instantiable :: instanceList;
deque<Instantiable*> Instantiable :: removeIList;


// Constructor
Instantiable :: Instantiable() : Drawable2() {
	instanceList.push_back(this);
}

// Updating
void Instantiable :: update(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Update Function
	Drawable2 :: update(gl, deltaTime);
}

// Drawing
void Instantiable :: draw(GraphicsOGL* gl, float deltaTime) {

	// Run Parent Class's Draw Function
	Drawable2 :: draw(gl, deltaTime);
}

// Destroy
void Instantiable :: destroy() {
	// Destroy in Parent Class
	Drawable2 :: destroy();

	// Add to List to be Removed
	removeIList.push_back(this);
}

// Remove Destroyed Objects
void Instantiable :: removeDestroyed() {
	Instantiable* inst;

	// Remove Destroyed Objects from List
	for(int i = 0; i < removeIList.size(); i++) {
		inst = removeIList[i];

		for(int j = 0; j < instanceList.size(); j++)
			if(instanceList[j] == inst) {
				instanceList.erase(instanceList.begin()+j);
				break;
			}
	}

	// Clear Remove List
	removeIList.clear();
}

