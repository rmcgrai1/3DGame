#include<iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"
#include "FrameTexture.h"

#include "item.h"
#include "invslot.h"
using namespace std;
TexturePack* InvSlot::Textures;
InvSlot::InvSlot(Item *newItem, int number, TexturePack *TP) {
	Textures = TP;
	ItemType = number?newItem:NULL; // sets to NULL if number==0
	count = number;
	maxCount = 64; // defaults to max of 64.  Can be changed with later call of SetMax
	int i;
	for(i=0;i<4;i++) {
		FrameIntPos[i] = 0;
	}
	MainSlots = new FrameTexture(Textures, "Images/Inventory/InvSlot");
}

void InvSlot::drawat(GraphicsOGL* gl, int x, int y, int x2, int y2, double rot) {
	if(ItemType) {
		if(!(FrameIntPos[0] || FrameIntPos[1] || FrameIntPos[2] || FrameIntPos[3])) { // if positions are at 0, calculate positions by drawing frame to NULL
			MainSlots->drawat(NULL, x, y, x2, y2, FrameIntPos); // don't draw anything, but use to calculate positions
		}
		string countStr = to_string(count);
		double xScale = (double)FrameIntPos[2]/60;
		double yScale = (double)FrameIntPos[4]/200;
		gl->drawStringScaled(FrameIntPos[0]+FrameIntPos[2]-16*countStr.length()*xScale,FrameIntPos[1]+FrameIntPos[3]-16*yScale,xScale,yScale,countStr);
		ItemType->DisplayAt(gl,FrameIntPos[0],FrameIntPos[1],FrameIntPos[2],FrameIntPos[3],rot);
	}
	MainSlots->drawat(gl, x, y, x2, y2, FrameIntPos);
}

void InvSlot::SetMax(int max) {
	maxCount = max;
}

int InvSlot::GetCount() {
	return count;
}

Item *InvSlot::GetItemType() {
	return ItemType;
}

int InvSlot::GetMax() {
	return maxCount;
}

int InvSlot::AddItem(Item *newItem, int number) {
	if(count!=0 && ItemType!=newItem) { // if already has something in slot, and it's not the same item type, don't change anything
		return number;
	} else if(number < 0) { // if negative amount added
		return number + RemoveCount(-1*number); // remove negative of amount, then calculate overflow from amount removed
	} else {
		count+=number; // add specified amount
		ItemType = newItem; // make sure item type is listed
		if(count<=maxCount) { // if there is not overflow, return 0
			return 0;
		} else { // there is overflow
			int overflow = count-maxCount; // calculate overflow
			count = maxCount; // reduce to maximum
			return overflow;
		}
	}
}

int InvSlot::AddCount(int number) {
	if(count==0) { // if empty, adding doesn't work because type of item isn't specified
		return number;
	} else {
		count+=number; // add specified amount
		if(count<=maxCount) { // if there is not overflow, return 0
			return 0;
		} else { // there is overflow
			int overflow = count-maxCount; // calculate overflow
			count = maxCount; // reduce to maximum
			return overflow;
		}
	}
}

int InvSlot::RemoveCount(int number) {
	if(number<0) { // if negative amount removed
		return number + AddCount(-1*number); // add positive amount, using overflow to calculate negative of amount added
	}
	count-=number; // remove specified amount
	if(count<=0) { // if all removed
		int removed = number+count; // find amount there were before
		ItemType = NULL; // set back to empty slot
		count = 0; // clear inventory amount to zero
		return removed; // return amount there were in slot before
	} else { // there is no overflow
		return number; // return amount removed
	}
}

int InvSlot::MoveTo(int number, InvSlot *Destination) {
	int SourceOverflow = (number<count)?0:(number-count); // calculate amount of overflow from source, if there is more moved than exist
	int DestOverflow = Destination->AddItem(this->ItemType, number-SourceOverflow); // add as many as possible to the destination, storing overflow amount
	int TotOverflow = SourceOverflow+DestOverflow; // calculate total overflow amount
	int AmountToRemove = number-TotOverflow; // calculate amount needed to be removed from source slot
	int AmountRemoved = RemoveCount(AmountToRemove); // remove required amount, storing actual amount removed
	int RemovedError = AmountRemoved - AmountToRemove; // calculate amount of error in removed amount, for error checking (should ALWAYS be 0)
	if(RemovedError) {
		cout << "ERROR: Incorrect amount of items removed from slot!!! (Should never happen!!!)\n";
		cout << RemovedError << " extra items removed!!!\n";
	}
	return TotOverflow;
}

int InvSlot::MoveFrom(int number, InvSlot *Source) {
	return Source->MoveTo(number, this); // use MoveTo function, created above with source and destination reversed
}

void InvSlot::SwapWith(InvSlot *Other) {
	InvSlot *temp = new InvSlot(NULL, 0, Textures);
	int Overflow = MoveTo(GetCount(), temp);
	if(Overflow) {
		cout << "WARNING: overflow of " << Overflow << " items when copying from [" << *this << "] to temporary [" << *temp << "]\n";
	}
	Overflow = MoveFrom(Other->GetCount(), Other);
	if(Overflow) {
		cout << "WARNING: overflow of " << Overflow << " items when copying to [" << *this << "] from [" << *Other << "]\n";
	}
	Overflow = temp->MoveTo(temp->GetCount(), Other);
	if(Overflow) {
		cout << "WARNING: overflow of " << Overflow << " items when copying from temporary [" << *temp << "] to [" << *Other << "]\n";
	}
	delete temp;
}

int *InvSlot::GetFrameIntPos() {
	return FrameIntPos;
}

ostream& operator<<(ostream& output, const InvSlot Slot) {
	if(Slot.ItemType) {
		output << *(Slot.ItemType) << ": " << Slot.count << "/" << Slot.maxCount;
	} else {
		output << "Empty: " << Slot.count << "/" << Slot.maxCount;
	}
	return output;
}
