#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "PosSpec.h"
#include "playerInv.h"
#include "menu.h"
using namespace std;

double Menu::ItemRot;

Menu::Menu() : Drawable2(TYPE_MENU) {
	Textures = new TexturePack("Resources");
	playerInventory = new playerInv;
	ShowMenu = 0;
	mouseX = 0;
	mouseY = 0;
	scrDim = new PosSpec(0,0,640,480);
	invDim = new PosSpec(0,0,640,480);
	updateDrawCoords(NULL);
	Cursor = Textures->newTexture("Images/Menus/Cursor.png", false);
	ItemRot = 45;
}

void Menu::draw(GraphicsOGL* gl, float deltaTime) {
	if(ShowMenu) { // only show anything if ShowMenu is true
		gl->setOrtho(); // switch to 2D mode
		//gl->disableShaders(); // disable any shaders (removed because of bug with cursor showing as white box)
		
		gl->drawTexture(mouseX, mouseY, Cursor);
		playerInventory->draw(gl, deltaTime);
		
		gl->setPerspective(); // switch back to 3D mode
	}
}

void Menu::update(GraphicsOGL* gl, float deltaTime) {
	InputController *Input = gl->getInputController();
	
	mouseX = Input->getMouseX();
	mouseY = Input->getMouseY();
	
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
		ShowMenu = !ShowMenu; // toggle showing menu
		updateDrawCoords(gl); // update the coordinates for drawing the menu (don't need updated more than once per opening of menu)
	}
	PrevKeyState = ThisKeyState; // record current key state in previous key state for next iteration
	
	if(ShowMenu) {
		playerInventory->update(Input, invDim, ItemRot);
	}
}

int Menu::getMenuShowStatus() {
	return ShowMenu;
}

void Menu::updateDrawCoords(GraphicsOGL* gl) {
	if(gl) {
		if(gl->getScreenWidth()!=scrDim->getWidth()) {
			scrDim->setWidth(gl->getScreenWidth());
			cout << "Menu screen width changed to " << scrDim->getWidth() << endl;
		}
		if(gl->getScreenHeight()!=scrDim->getHeight()) {
			scrDim->setHeight(gl->getScreenHeight());
			cout << "Menu screen height changed to " << scrDim->getHeight() << endl;
		}
	} else { // gl is NULL - must assume default screen dimensions (should happen in constructor)
		scrDim->changeDim(640,480);
		cout << "Menu screen dimensions defaulted to " << scrDim->getWidth() << "x" << scrDim->getHeight() << endl;
	}
	
	invDim->setTopLeft(scrDim->getWidth()/10,scrDim->getHeight()/5);
	invDim->changeDim(scrDim->getWidth()*4/5,scrDim->getHeight()*3/5);
}

ostream& operator<<(ostream& output, const Menu menu) {
	output << "Menus:\n";
	if(menu.ShowMenu) {
		output << "Player Inventory:\n";
		output << (*menu.playerInventory);
	} else {
		output << "None shown\n";
	}
	return output;
}
