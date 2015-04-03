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

Inventory::Inventory() : Drawable2(TYPE_INVENTORY) {
	Textures = new TexturePack("Resources");
	int i;
	for(i=0;i<27;i++) {
		Slots[i] = new InvSlot(NULL, 0, Textures);
	}
	CursorSlot = new InvSlot(NULL, 0, Textures);
	ShowInventory = 0;
	mouseX = 0;
	mouseY = 0;
	updateDrawCoords(NULL);
	Cursor = Textures->newTexture("Images/Menus/Cursor.png", false);
	ItemRot = 45;
	
	//TEST CODE to add some items to slots
	items.push_back(new Item("stone", "Images/Items/stone", Textures));
	Slots[8]->AddItem(items.back(), 54);
	items.push_back(new Item("dirt", "Images/Items/dirt", Textures));
	Slots[10]->AddItem(items.back(), 42);
	
}

void Inventory::draw(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("inventory.cpp, draw()");

	/*gl->disableShaders();
	gl->setOrtho(); // switch to 2D mode
	gl->setColor(2147483647*0.5,2147483647*0.5,2147483647*0.5); // set color to gray
	cout << "Drawing inventory!\n";
	gl->fillRect(gl->getScreenWidth()-40, gl->getScreenHeight()-40, gl->getScreenWidth()-20, gl->getScreenHeight()-20);
	Slots[8]->drawat(gl, gl->getScreenWidth()-40, gl->getScreenHeight()-40, gl->getScreenWidth()-20, gl->getScreenHeight()-20);
	gl->setColor(2147483647*1,2147483647*1,2147483647*1); // set color back to white
	gl->setPerspective(); // switch back to 3D mode
	*/

	if(ShowInventory) { // only show anything if ShowInventory is true
		gl->setOrtho(); // switch to 2D mode
		//gl->disableShaders(); // disable any shaders (removed because of bug with cursor showing as white box)
		
		gl->drawTexture(mouseX, mouseY, Cursor);
		int row, col, i, x, y;
		for(row=0;row<3;row++) {
			for(col=0;col<9;col++) {
				i = row*9+col;
				x = leftx + slotwidth*col;
				y = topy + slotheight*row;
				
				Slots[i]->drawat(gl, x, y, x+slotwidth, y+slotheight, ItemRot);
			}
		}
		
		
		
		gl->setPerspective(); // switch back to 3D mode
	}
}

void Inventory::update(GraphicsOGL* gl, float deltaTime) {
	InputController *Input = gl->getInputController();
	
	mouseX = Input->getMouseX();
	mouseY = Input->getMouseY();
	
	InvSlot *HoveredItem = itemAt(mouseX, mouseY);
	
	// Update rotation of items
	ItemRot+=0.2;
	if(ItemRot>=360) {
		ItemRot-=360;
	}
	
	// React to 'I'
	static int PrevKeyState = 0;
	int ThisKeyState = Input->checkLetter('i'); // get current state of the key
	if(ThisKeyState && !PrevKeyState) { // if key just pressed down
		ItemRot = 45; // initialize rotation of items to 45 degrees
		ShowInventory = !ShowInventory; // toggle showing inventory
		updateDrawCoords(gl); // update the coordinates for drawing the inventory (don't need updated more than once per opening of menu)
	}
	PrevKeyState = ThisKeyState; // record current key state in previous key state for next iteration
	
	// React to left mouse
	static int PrevLeftMouseState = 0;
	int ThisLeftMouseState = Input->checkLeftMouse(); // get current state of button
	if(ThisLeftMouseState && !PrevLeftMouseState) {
		// Left mouse button pressed
		if(HoveredItem) {
			cout << "Swapped [" << *CursorSlot << "] in cursor with [" << *HoveredItem << "]\n";
			CursorSlot->SwapWith(HoveredItem);
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
		if(HoveredItem) {
			if(CursorSlot->GetCount()) { // there is something picked up
				cout << "Moved one from [" << *CursorSlot << "] in cursor to slot with [" << *HoveredItem << "]\n";
				CursorSlot->MoveTo(1, HoveredItem);
			} else { // there is nothing picked up
				cout << "Moved half from [" << *HoveredItem << "] to cursor with [" << *CursorSlot << "]\n";
				CursorSlot->MoveFrom((HoveredItem->GetCount())/2, HoveredItem);
			}
		}
	} else if(!ThisRightMouseState && PrevRightMouseState) {
		// Right mouse button released
	} else if(ThisRightMouseState) {
		// Right mouse button is currently held down
	}
	PrevRightMouseState = ThisRightMouseState; // record current button state in previous button state for next iteration
}

int Inventory::getInventoryShowStatus() {
	return ShowInventory;
}

void Inventory::updateDrawCoords(GraphicsOGL* gl) {
	if(gl) {
		if(gl->getScreenWidth()!=scrwidth) {
			scrwidth = gl->getScreenWidth();
			cout << "Inventory screen width changed to " << scrwidth << endl;
		}
		if(gl->getScreenHeight()!=scrheight) {
			scrheight = gl->getScreenHeight();
			cout << "Inventory screen height changed to " << scrheight << endl;
		}
	} else { // gl is NULL - must assume default screen dimensions (should happen in constructor)
		scrwidth = 640;
		scrheight = 480;
		cout << "Inventory screen dimensions defaulted to " << scrwidth << "x" << scrheight << endl;
	}
	leftx = scrwidth/10;
	topy = scrheight/5;
	invwidth = scrwidth*4/5;
	invheight = scrheight*3/5;
	slotwidth = invwidth/9;
	slotheight = invheight/3;
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

ostream& operator<<(ostream& output, const Inventory inv) {
	int i;
	for(i=0;i<27;i++) {
		output << "[" << i << "] " << inv.Slots[i] << endl;
	}
	return output;
}
