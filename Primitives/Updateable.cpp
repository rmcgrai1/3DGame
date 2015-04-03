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
<<<<<<< HEAD

	bool isInvOpen = gl->getInventory()->getInventoryShowStatus();

	for(int i = 0; i < si; i++) {
		if(updateableList[i] == NULL)
			continue;

		if(!isInvOpen || updateableList[i]->oType == TYPE_INVENTORY)
=======
	bool isInvOpen = gl->getMenu()->getMenuShowStatus();

	for(int i = 0; i < si; i++) {
		if(!isInvOpen || updateableList[i]->oType == TYPE_MENU)
>>>>>>> 7214d79ba1fa5417571a7679619f5a5f5db13f52
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
