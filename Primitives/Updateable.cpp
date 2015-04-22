// Updateable.cpp


#include <iostream>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
using namespace std;


deque<Updateable*> Updateable :: updateableList;
deque<Updateable*> Updateable :: removeUList;

Updateable :: Updateable() {

	//cout << "No type specified for some UPDATEABLE object." << endl;

	oType = TYPE_NONE;
	updateableList.push_back(this);

	doUpdates = true;
}

Updateable :: Updateable(int newType) {
	oType = newType;
	updateableList.push_back(this);
	doUpdates = true;
}

void Updateable :: updateAll(GraphicsOGL* gl, float deltaTime) {
	int si = updateableList.size();

	bool isInvOpen = gl->getMenu()->getMenuShowStatus();
	bool isTextBoxOpen = gl->getTextController()->isTextBoxOpen();

	Updateable* u;

	for(int i = 0; i < si; i++) {
		u = updateableList[i];

		if(u->doUpdates)
			if((!isInvOpen && !isTextBoxOpen) || u->oType == TYPE_MENU)
				u->update(gl, deltaTime);
	}
}
		
void Updateable :: update(GraphicsOGL* gl, float deltaTime) {
}

void Updateable :: destroy() {
	removeUList.push_back(this);
}

void Updateable :: removeDestroyed() {
	Updateable* inst;

	for(int i = 0; i < removeUList.size(); i++) {
		inst = removeUList[i];

		for(int j = 0; j < updateableList.size(); j++)
			if(updateableList[j] == inst) {
				updateableList.erase(updateableList.begin()+j);
				break;
			}
	}

	removeUList.clear();
}
