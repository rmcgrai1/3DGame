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
		int getInventoryShowStatus(); // returns whether the inventory is being shown (may be needed for pausing execution of game, etc.)
		void updateDrawCoords(GraphicsOGL*);
		int posInRange(int x, int y, int x1, int y1, int x2, int y2);
		InvSlot *itemAt(int x, int y);
	private:
		InvSlot *CursorSlot;
		InvSlot *Slots[27];
		vector<Item*> items;
		TexturePack *Textures;
		
		Texture *Cursor;
		
		int ShowInventory;
		int mouseX;
		int mouseY;
		
		int scrwidth,scrheight;
		int leftx,topy;
		int invwidth,invheight;
		int slotwidth,slotheight;
		static double ItemRot;
};

#endif