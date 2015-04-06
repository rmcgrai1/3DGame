#ifndef INVSLOT_H
#define INVSLOT_H

#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"
#include "FrameTexture.h"
#include "PosSpec.h"

#include "item.h"
using namespace std;
class InvSlot {
	friend ostream& operator<<(ostream&, const InvSlot);
	public:
		InvSlot(Item *newItem = NULL, int number = 0, TexturePack *TP = new TexturePack); // constructor: if number is 0, item is always "empty"
		void drawat(GraphicsOGL* gl, PosSpec *Dim, double rot); // draws the slot (and contents) at this position
		void SetMax(int max); // sets the maximum count of items for this slot
		int GetCount(); // returns the number of items in this slot
		Item *GetItemType(); // returns the type of item that is in the slot
		int GetMax(); // returns the maximum count of items in the slot
		int AddItem(Item *newItem, int number); // adds items of type "item" to the slot, if matches the currently existing item type, or is empty
		                                      // also returns overflowed amount
		int AddCount(int number); // adds specified amount to the slot, returning the overflow amount -- ONLY USE IF ALREADY CHECKED THE CURRENT ITEM ID
		int RemoveCount(int number); // removes specified amount from the slot, returning number removed (in case of overflow, returns amount previously in slot)
		int MoveTo(int number, InvSlot *Destination); // moves specified number of items into Destination, returning the amount of overflow
		int MoveFrom(int number, InvSlot *Source); // moves specified number of items from Source, returning the amount of overflow
		void SwapWith(InvSlot *Other); // switches the contents of slot with other slot
		PosSpec *GetFrameIntPos();
	private:
		Item *ItemType;
		int count;
		int maxCount;
		
		FrameTexture *MainSlots;
		//int FrameIntPos[4];
		PosSpec *FrameIntPos;
		static TexturePack *Textures;
};

#endif