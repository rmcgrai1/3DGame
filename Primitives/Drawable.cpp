// Drawable.cpp
// Ryan McGrail

#include <iostream>
#include <map>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
#include "Drawable.h"
using namespace std;


SortedList<Drawable2*> Drawable2 :: drawableList;


// Constructor
Drawable2 :: Drawable2() : Updateable() {

	fidelity = 1;
	isOnScreen = true;
	visible = true;
	drawableList.add(this);
}

// Constructor w/ Type
Drawable2 :: Drawable2(int type) : Updateable(type) {

	fidelity = 1;
	isOnScreen = true;
	visible = true;
	drawableList.add(this);
}

// Checking if Onscreen (Updating Value)
bool Drawable2 :: checkOnScreen(GraphicsOGL* gl) {
	fidelity = 1;
	isOnScreen = true;
	return true;
}

// Getting if Onscreen (Checking Variable)
bool Drawable2 :: getOnScreen() {
	return isOnScreen;
}

// Drawing All Drawable Objects
void Drawable2 :: drawAll(GraphicsOGL* gl, float deltaTime) {
	int si = drawableList.size();

	// Loop through Drawable Objects
	Drawable2* cur;
	for(int i = 0; i < si; i++) {

		cur = drawableList[i];

		// If Object is Null, Skip!
		if(cur == NULL)
			continue;

		// If Object is Visible and Onscreen, Draw!
		if(cur->visible)
			if(cur->checkOnScreen(gl))
				cur->draw(gl, deltaTime);
	}
}

// Updating
void Drawable2 :: update(GraphicsOGL* gl, float deltaTime) {
	Updateable :: update(gl, deltaTime);
}

// Drawing
void Drawable2 :: draw(GraphicsOGL* gl, float deltaTime) {
}

// Setting Visibility
void Drawable2 :: setVisible(int newV) {
	visible = newV;
}

// Destroying Object
void Drawable2 :: destroy() {
	Updateable :: destroy();
	drawableList.destroy(this);
}

// Removing Destroyed Objects
void Drawable2 :: removeDestroyed() {
	drawableList.removeDestroyed();
}
