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
Inventory::Inventory() {
	Textures = new TexturePack("Resources");
	int i;
	for(i=0;i<27;i++) {
		Slots[i] = new InvSlot(NULL, 0, Textures);
	}
	ShowInventory = 0;
	mouseX = 0;
	mouseY = 0;
	updateDrawCoords(NULL);
	Cursor = Textures->newTexture("Images/Inventory/Cursor.png", false);
	
	//TEST CODE to add some items to slots
	items.push_back(new Item("stone", "Images/Items/stone", Textures));
	Slots[8]->AddItem(items.back(), 54);
	items.push_back(new Item("dirt", "Images/Items/dirt", Textures));
	Slots[10]->AddItem(items.back(), 42);
	
}

void Inventory::draw(GraphicsOGL* gl, float deltaTime) {
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
				
				Slots[i]->drawat(gl, x, y, x+slotwidth, y+slotheight);
			}
		}
		
		
		
		gl->setPerspective(); // switch back to 3D mode
	}
}

void Inventory::update(GraphicsOGL* gl, float deltaTime) {
	InputController *Input = gl->getInputController();
	
	// React to 'I'
	static int PrevKeyState = 0;
	int ThisKeyState = Input->checkLetter('i'); // get current state of the key
	if(ThisKeyState && !PrevKeyState) { // if key just pressed down
		ShowInventory = !ShowInventory; // toggle showing inventory
		updateDrawCoords(gl); // update the coordinates for drawing the inventory (don't need updated more than once per opening of menu)
	}
	PrevKeyState = ThisKeyState; // record current key state in previous key state for next iteration
	
	// React to left mouse
	static int PrevLeftMouseState = 0;
	int ThisLeftMouseState = Input->checkLeftMouse(); // get current state of button
	if(ThisLeftMouseState && !PrevLeftMouseState) {
		// Left mouse button pressed
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
	} else if(!ThisRightMouseState && PrevRightMouseState) {
		// Right mouse button released
	} else if(ThisRightMouseState) {
		// Right mouse button is currently held down
	}
	PrevRightMouseState = ThisRightMouseState; // record current button state in previous button state for next iteration
	
	mouseX = Input->getMouseX();
	mouseY = Input->getMouseY();
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

ostream& operator<<(ostream& output, const Inventory inv) {
	int i;
	for(i=0;i<27;i++) {
		output << "[" << i << "] " << inv.Slots[i] << endl;
	}
	return output;
}