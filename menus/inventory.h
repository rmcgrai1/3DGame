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
class Inventory {
	friend ostream& operator<<(ostream&, const Inventory);
	public:
		Inventory(); // constructor
		void draw(GraphicsOGL*, float);
		void update(int x, int y, int invwidth, int invheight, double Rot);
		void leftclick(int x, int y, InvSlot *CursorSlot);
		void rightclick(int x, int y, InvSlot *CursorSlot);
		void updateDrawCoords(int x, int y, int fullwidth, int fullheight);
		int posInRange(int x, int y, int x1, int y1, int x2, int y2);
		InvSlot *itemAt(int x, int y);
		int *GetFramePos();
	private:
		InvSlot *Slots[27];
		vector<Item*> items;
		TexturePack *Textures;
		
		Texture *Cursor;
		
		int ShowInventory;
		int mouseX;
		int mouseY;
		
		int sizepos[4];
		int leftx,topy;
		int allwidth,allheight;
		int slotwidth,slotheight;
		static double ItemRot;
};

#endif
