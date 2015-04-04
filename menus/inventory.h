#ifndef INVENTORY_H
#define INVENTORY_H

#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "PosSpec.h"
#include "item.h"
#include "invslot.h"
using namespace std;
class Inventory {
	friend ostream& operator<<(ostream&, const Inventory);
	public:
		Inventory(); // constructor
		void draw(GraphicsOGL*, float);
		void update(PosSpec *Dim, double Rot);
		void leftclick(int x, int y, InvSlot *CursorSlot);
		void rightclick(int x, int y, InvSlot *CursorSlot);
		void updateDrawCoords(PosSpec *Dim);
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
		vector<PosSpec*> slotDims;
		//int slotwidth,slotheight;
		static double ItemRot;
};

#endif
