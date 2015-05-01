// Updateable.cpp
// Ryan McGrail

#include <iostream>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
using namespace std;


deque<Updateable*> Updateable :: updateableList;
deque<Updateable*> Updateable :: removeUList;

// Constructor
Updateable :: Updateable() {

	oType = TYPE_NONE;
	updateableList.push_back(this);

	doUpdates = true;
}

// Constructor w/ Type
Updateable :: Updateable(int newType) {
	doUpdates = true;
	oType = newType;
	updateableList.push_back(this);
	doUpdates = true;
}

// Update All Objects
void Updateable :: updateAll(GraphicsOGL* gl, float deltaTime) {
	int si = updateableList.size();

	bool isInvOpen = gl->getMenu()->getMenuShowStatus();
	bool isTextBoxOpen = gl->getTextController()->isTextBoxOpen();

	Updateable* u;

	// Loop through Updateable Objects
	for(int i = 0; i < si; i++) {
		u = updateableList[i];

		// If Should be Updating, Update!
		if(u->doUpdates)
			if((!isInvOpen && !isTextBoxOpen) || u->oType == TYPE_MENU)
				u->update(gl, deltaTime);
	}
}
		
// Updating
void Updateable :: update(GraphicsOGL* gl, float deltaTime) {
}

// Destroying Object
void Updateable :: destroy() {
	removeUList.push_back(this);
}

// Removing Destroyed Objects
void Updateable :: removeDestroyed() {
	Updateable* inst;

	// Loop through Destroyed Objects, Remove from List
	for(int i = 0; i < removeUList.size(); i++) {
		inst = removeUList[i];

		// Find Object in List, Erase
		for(int j = 0; j < updateableList.size(); j++)
			if(updateableList[j] == inst) {
				updateableList.erase(updateableList.begin()+j);
				break;
			}
	}

	// Clear Removed List
	removeUList.clear();
}
