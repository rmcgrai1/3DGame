#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

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
	updateDrawCoords(64,96,640,480);
	Cursor = Textures->newTexture("Images/Menus/Cursor.png", false);
	ItemRot = 45;
	
	//TEST CODE to add some items to slots
	items.push_back(new Item("stone", "Images/Items/stone", Textures));
	Slots[8]->AddItem(items.back(), 54);
	items.push_back(new Item("dirt", "Images/Items/dirt", Textures));
	Slots[10]->AddItem(items.back(), 42);
	
}

void Inventory::draw(GraphicsOGL* gl, float deltaTime) {
	int row, col, i, x, y;
	for(row=0;row<3;row++) {
		for(col=0;col<9;col++) {
			i = row*9+col;
			x = leftx + slotwidth*col;
			y = topy + slotheight*row;
			
			Slots[i]->drawat(gl, x, y, x+slotwidth, y+slotheight, ItemRot);
		}
	}
}

void Inventory::update(int x, int y, int invwidth, int invheight, double Rot) {
	updateDrawCoords(x,y,invwidth,invheight);
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

void Inventory::updateDrawCoords(int x, int y, int fullwidth, int fullheight) {
	leftx = x;
	topy = y;
	allwidth = fullwidth;
	allheight = fullheight;
	slotwidth = allwidth/9;
	slotheight = allheight/3;
	
	sizepos[0] = leftx;
	sizepos[1] = topy;
	sizepos[2] = allwidth;
	sizepos[3] = allheight;
}

int Inventory::posInRange(int x, int y, int x1, int y1, int x2, int y2) {
	if((x1<=x && x<=x2) || (x2<=x && x<=x1)) {
		if((y1<=y && y<=y2) || (y2<=y && y<=y1)) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

InvSlot *Inventory::itemAt(int x, int y) {
	int i;
	for(i=0;i<27;i++) {
		InvSlot *ThisSlot = Slots[i];
		int *Frame = ThisSlot->GetFrameIntPos();
		if(posInRange(x,y,Frame[0],Frame[1],Frame[0]+Frame[2],Frame[1]+Frame[3])) {
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
