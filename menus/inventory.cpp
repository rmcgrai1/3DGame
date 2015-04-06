#include<iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "PosSpec.h"
#include "item.h"
#include "invslot.h"
#include "inventory.h"
using namespace std;

double Inventory::ItemRot;

Inventory::Inventory() {
	Textures = new TexturePack("Resources");
	int i;
	for(i=0;i<27;i++) {
		Slots[i] = new InvSlot(NULL, 0, Textures);
	}
	ShowInventory = 0;
	mouseX = 0;
	mouseY = 0;
	PosSpec *tempDim = new PosSpec(64,96,640,480);
	updateDrawCoords(tempDim);
	delete [] tempDim;
	Cursor = Textures->newTexture("Images/Menus/Cursor.png", false);
	ItemRot = 45;
	
	//TEST CODE to add some items to slots
	items.push_back(new Item("stone", "Images/Items/stone", Textures));
	Slots[8]->AddItem(items.back(), 54);
	items.push_back(new Item("dirt", "Images/Items/dirt", Textures));
	Slots[10]->AddItem(items.back(), 42);
	
}

void Inventory::draw(GraphicsOGL* gl, float deltaTime) {
	int i = 0;
	vector<PosSpec*>::iterator j;
	for(j=slotDims.begin();j!=slotDims.end();j++) {
		Slots[i]->drawat(gl, (*j), ItemRot);
		i++;
	}
}

void Inventory::update(PosSpec *Dim, double Rot) {
	updateDrawCoords(Dim);
	// Update rotation of items
	ItemRot = Rot;
}

void Inventory::leftclick(int x, int y, InvSlot *CursorSlot) {
	InvSlot *HoveredItem = itemAt(x, y);
	
	if(HoveredItem) {
		cout << "Swapped [" << *CursorSlot << "] in cursor with [" << *HoveredItem << "]\n";
		CursorSlot->SwapWith(HoveredItem);
	}
}

void Inventory::rightclick(int x, int y, InvSlot *CursorSlot) {
	InvSlot *HoveredItem = itemAt(x,y);
	
	if(HoveredItem) {
		if(CursorSlot->GetCount()) { // there is something picked up
			cout << "Moved one from [" << *CursorSlot << "] in cursor to slot with [" << *HoveredItem << "]\n";
			CursorSlot->MoveTo(1, HoveredItem);
		} else { // there is nothing picked up
			cout << "Moved half from [" << *HoveredItem << "] to cursor with [" << *CursorSlot << "]\n";
			CursorSlot->MoveFrom((HoveredItem->GetCount())/2, HoveredItem);
		}
	}
}

void Inventory::updateDrawCoords(PosSpec *Dim) {
	leftx = Dim->getLeftX();
	topy = Dim->getTopY();
	allwidth = Dim->getWidth();
	allheight = Dim->getHeight();
	//slotwidth = allwidth/9;
	//slotheight = allheight/3;
	Dim->UpdateSplit(9,3, &slotDims);
	sizepos[0] = leftx;
	sizepos[1] = topy;
	sizepos[2] = allwidth;
	sizepos[3] = allheight;
}

InvSlot *Inventory::itemAt(int x, int y) {
	int i;
	for(i=0;i<27;i++) {
		InvSlot *ThisSlot = Slots[i];
		PosSpec *Frame = ThisSlot->GetFrameIntPos();
		if(Frame->isInside(x,y)) {
			return ThisSlot;
		}
	}
	return NULL;
}

int *Inventory::GetFramePos() {
	return sizepos;
}


ostream& operator<<(ostream& output, const Inventory inv) {
	int i;
	for(i=0;i<27;i++) {
		output << "[" << i << "] " << (*inv.Slots[i]) << endl;
	}
	return output;
}
