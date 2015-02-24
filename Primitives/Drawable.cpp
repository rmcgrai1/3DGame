// Drawable.cpp


#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
#include "Drawable.h"

deque<Drawable*> Drawable :: drawableList;

Drawable :: Drawable() : Updateable() {
	drawableList.push_back(this);
}

void Drawable :: drawAll(GraphicsOGL* gl, float deltaTime) {
	int si = drawableList.size();

	for(int i = 0; i < si; i++)
		drawableList[i]->draw(gl, deltaTime);
}

void Drawable :: update(GraphicsOGL* gl, float deltaTime) {
	Updateable :: update(gl, deltaTime);
}

void Drawable :: draw(GraphicsOGL* gl, float deltaTime) {
}
