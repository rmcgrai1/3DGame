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
	
	items.push_back(new Item);
	items.back()->SetType("stone");
	Slots[8].AddItem(items.back(), 54);
	items.push_back(new Item);
	items.back()->SetType("dirt");
	Slots[10].AddItem(items.back(), 42);
	
}

void Inventory::draw(GraphicsOGL* gl, float deltaTime) {
	gl->setOrtho(); // switch to 2D mode
	gl->setColor(2147483647*0.5,2147483647*0.5,2147483647*0.5); // set color to gray
	cout << "Drawing inventory!\n";
	gl->fillRect(gl->getScreenWidth()-40, gl->getScreenHeight()-40, gl->getScreenWidth()-20, gl->getScreenHeight()-20);
	Slots[8].drawat(gl, gl->getScreenWidth()-40, gl->getScreenHeight()-40, gl->getScreenWidth()-20, gl->getScreenHeight()-20);
	gl->setColor(2147483647*1,2147483647*1,2147483647*1); // set color back to white
	gl->setPerspective(); // switch back to 3D mode
}

void Inventory::update(GraphicsOGL* gl, float deltaTime) {
	/*cout << "Inventory:\n";
	cout << (*this);
	Textures->ChangeFolder("Resources");*/
}

ostream& operator<<(ostream& output, const Inventory inv) {
	int i;
	for(i=0;i<27;i++) {
		output << "[" << i << "] " << inv.Slots[i] << endl;
	}
	return output;
}