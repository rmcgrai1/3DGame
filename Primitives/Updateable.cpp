// Updateable.cpp


#include <iostream>
#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
using namespace std;


deque<Updateable*> Updateable :: updateableList;
deque<Updateable*> Updateable :: removeUList;

Updateable :: Updateable() {

	cout << "No type specified for some UPDATEABLE object." << endl;

	oType = TYPE_NONE;
	updateableList.push_back(this);
}

Updateable :: Updateable(int newType) {
	oType = newType;
	updateableList.push_back(this);
}

void Updateable :: updateAll(GraphicsOGL* gl, float deltaTime) {
	int si = updateableList.size();

	bool isInvOpen = gl->getMenu()->getMenuShowStatus();
	bool isTextBoxOpen = gl->getTextController()->isTextBoxOpen();

	for(int i = 0; i < si; i++) {
		if((!isInvOpen && !isTextBoxOpen) || updateableList[i]->oType == TYPE_MENU)
			updateableList[i]->update(gl, deltaTime);
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
