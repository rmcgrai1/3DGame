// Drawable.cpp


#include <iostream>
#include <map>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
#include "Drawable.h"
using namespace std;


SortedList<Drawable2*> Drawable2 :: drawableList;


Drawable2 :: Drawable2() : Updateable() {

	visible = true;
	drawableList.add(this);
}

Drawable2 :: Drawable2(int type) : Updateable(type) {

	visible = true;
	drawableList.add(this);
}

void Drawable2 :: drawAll(GraphicsOGL* gl, float deltaTime) {
	int si = drawableList.size();

	Drawable2* cur;
	for(int i = 0; i < si; i++) {

		cur = drawableList[i];

		if(cur == NULL)
			continue;

		if(cur->visible)
			cur->draw(gl, deltaTime);
	}
}

void Drawable2 :: update(GraphicsOGL* gl, float deltaTime) {
	Updateable :: update(gl, deltaTime);
}

void Drawable2 :: draw(GraphicsOGL* gl, float deltaTime) {
}

void Drawable2 :: setVisible(int newV) {
	visible = newV;
}

void Drawable2 :: destroy() {
	Updateable :: destroy();
	drawableList.destroy(this);
}

void Drawable2 :: removeDestroyed() {
	drawableList.removeDestroyed();
}
