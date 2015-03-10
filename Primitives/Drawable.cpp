// Drawable.cpp


#include <iostream>
#include <map>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
#include "Drawable.h"
using namespace std;


deque<Drawable2*> Drawable2 :: drawableList;
deque<Drawable2*> Drawable2 :: hudList;


Drawable2 :: Drawable2() : Updateable() {

	cout << "No type specified for some drawable object." << endl;

	drawableList.push_back(this);
}

Drawable2 :: Drawable2(int type) : Updateable() {
	drawableList.push_back(this);
}

void Drawable2 :: drawAll(GraphicsOGL* gl, float deltaTime) {
	int si = drawableList.size();

	for(int i = 0; i < si; i++)
		drawableList[i]->draw(gl, deltaTime);
}

void Drawable2 :: update(GraphicsOGL* gl, float deltaTime) {
	Updateable :: update(gl, deltaTime);
}

void Drawable2 :: draw(GraphicsOGL* gl, float deltaTime) {
}
