// Updateable.cpp


#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"


deque<Updateable*> Updateable :: updateableList;

Updateable :: Updateable() {
	updateableList.push_back(this);
}

void Updateable :: updateAll(GraphicsOGL* gl, float deltaTime) {
	int si = updateableList.size();

	for(int i = 0; i < si; i++)
		updateableList[i]->update(gl, deltaTime);
}
		
void Updateable :: update(GraphicsOGL* gl, float deltaTime) {
}
