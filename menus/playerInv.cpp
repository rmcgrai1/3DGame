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
#include "playerInv.h"
using namespace std;

//double playerInv::ItemRot;

playerInv::playerInv() {
	Textures = new TexturePack("Resources");
	CursorSlot = new InvSlot(NULL, 0, Textures);
	//initialize all inventories here
	inv = new Inventory;
	mouseX = 0;
	mouseY = 0;
	updateDrawCoords(64,96,640,480);
	Cursor = Textures->newTexture("Images/Menus/Cursor.png", false);
}

void playerInv::draw(GraphicsOGL* gl, float deltaTime) {
	//draw all inventories here
	inv->draw(gl, deltaTime);
}

void playerInv::update(InputController* Input, int x, int y, int invwidth, int invheight, double Rot) {
	updateDrawCoords(x, y, invwidth, invheight);
	
	//update all inventories here
	inv->update(leftx,topy,inswidth,insheight,Rot);
	
	mouseX = Input->getMouseX();
	mouseY = Input->getMouseY();
	
	Inventory *HoveredInv = InvAt(mouseX, mouseY);
	
	// React to left mouse
	static int PrevLeftMouseState = 0;
	int ThisLeftMouseState = Input->checkLeftMouse(); // get current state of button
	if(ThisLeftMouseState && !PrevLeftMouseState) {
		// Left mouse button pressed
		if(HoveredInv) {
			HoveredInv->leftclick(mouseX, mouseY, CursorSlot);
		}
	} else if(!ThisLeftMouseState && PrevLeftMouseState) {
		// Left mouse button released
	} else if(ThisLeftMouseState) {
		// Left mouse button is currently held down
	}
	PrevLeftMouseState = ThisLeftMouseState; // record current button state in previous button state for next iteration
	
	// React to right mouse
	static int PrevRightMouseState = 0;
	int ThisRightMouseState = Input->checkRightMouse(); // get current state of button
	if(ThisRightMouseState && !PrevRightMouseState) {
		// Right mouse button pressed
		inv->rightclick(mouseX, mouseY, CursorSlot);
		if(HoveredInv) {
			HoveredInv->rightclick(mouseX, mouseY, CursorSlot);
		}
	} else if(!ThisRightMouseState && PrevRightMouseState) {
		// Right mouse button released
	} else if(ThisRightMouseState) {
		// Right mouse button is currently held down
	}
	PrevRightMouseState = ThisRightMouseState; // record current button state in previous button state for next iteration
}

void playerInv::updateDrawCoords(int x, int y, int fullwidth, int fullheight) {
	leftx = x+fullwidth/10;
	topy = y+fullheight/5;
	inswidth = fullwidth*4/5;
	insheight = fullheight*3/5;
}

int playerInv::posInRange(int x, int y, int x1, int y1, int x2, int y2) {
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

Inventory *playerInv::InvAt(int x, int y) {
	//check all inventories here
	int *Frame = inv->GetFramePos();
	if(posInRange(x,y,Frame[0],Frame[1],Frame[0]+Frame[2],Frame[1]+Frame[3])) {
		return inv;
	}
	
	return NULL;
}

ostream& operator<<(ostream& output, const playerInv inv) {
	//output all inventories here
	output << "Item slots:\n";
	output << (*inv.inv);
	output << "Cursor:\n";
	output << (*inv.CursorSlot) << endl;
	return output;
}
