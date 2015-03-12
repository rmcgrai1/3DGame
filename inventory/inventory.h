#ifndef INVENTORY_H
#define INVENTORY_H

#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "item.h"
#include "invslot.h"
using namespace std;
class Inventory : public Drawable2 {
	friend ostream& operator<<(ostream&, const Inventory);
	public:
		Inventory(); // constructor
		void draw(GraphicsOGL*, float);
		void update(GraphicsOGL*, float);
	private:
		InvSlot *Slots[27];
		vector<Item*> items;
		TexturePack *Textures;
};

#endif