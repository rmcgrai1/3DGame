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

	bool isInvOpen = gl->getInventory()->getInventoryShowStatus();

	for(int i = 0; i < si; i++) {
		if(updateableList[i] == NULL)
			continue;

		if(!isInvOpen || updateableList[i]->oType == TYPE_INVENTORY)
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
