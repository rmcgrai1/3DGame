#include<iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "item.h"
#include "invslot.h"
using namespace std;
Texture* InvSlot::Sprites[9];
int *InvSlot::SpriteDim[9];
TexturePack* InvSlot::Textures;
InvSlot::InvSlot(Item *newItem, int number, TexturePack *TP) {
	Textures = TP;
	ItemType = number?newItem:NULL; // sets to NULL if number==0
	count = number;
	maxCount = 64; // defaults to max of 64.  Can be changed with later call of SetMax
	prevheight = 0;
	prevwidth = 0;
	int i;
	for(i=0;i<9;i++) {
		SpriteDim[i] = Textures->newDim("Images/Inventory/InvSlot/" + to_string(i) + ".dim"); // load each of these dimensions from a different file, and the texture from a different file
		Sprites[i] = Textures->newTexture("Images/Inventory/InvSlot/" + to_string(i) + ".png", false); // save texture in Sprite
	}
}

void InvSlot::drawat(GraphicsOGL* gl, int x, int y, int x2, int y2) {
	UpdateDrawCoords(x2-x, y2-y);
	int blank = 0;
	int *dummy = &blank;
	int curX = x;
	int curY[3];
	int i;
	for(i=0;i<3;i++) {
		curY[i] = y;
	}
	for(i=0;i<9;i++) {
		int xNum = ((i%3)==1)?(SpriteNums[i/3]):1;
		int yNum = ((i/3)==1)?(SpriteNums[(i%3)+3]):1;
		if((i%3)==0) {
			curX = x;
		}
		tileTexture(gl,curX,curY[i%3],SpriteDim[i][0],SpriteDim[i][1],xNum,yNum,SpriteScales[0],SpriteScales[1],&curX,&curY[i%3],Sprites[i]);
	}
	//tileTexture(gl,curX,curY,SpriteDim[0][0],SpriteDim[0][1],1,1,SpriteScales[0],SpriteScales[1],&curX,dummy,Sprites[0]);
	//tileTexture(gl,curX,curY,SpriteDim[1][0],SpriteDim[1][1],SpriteNums[0],1,SpriteScales[0],SpriteScales[1],&curX,dummy,Sprites[1]);
	//tileTexture(gl,curX,curY,SpriteDim[2][0],SpriteDim[2][1],1,1,SpriteScales[0],SpriteScales[1],&curX,dummy,Sprites[2]);
	//gl->drawTextureScaled(x, y, SpriteScales[0], SpriteScales[1], Sprites[0]);
}

void InvSlot::tileTexture(GraphicsOGL* gl, int x, int y, int width, int height, int xNum, int yNum, double xScale, double yScale, int *finalX, int *finalY, Texture* Tex) {
	int i,j;
	for(i=0;i<xNum;i++) {
		for(j=0;j<yNum;j++) {
			gl->drawTextureScaled(x+i*width*xScale, y+j*height*yScale, xScale, yScale, Tex);
		}
	}
	(*finalX) = x+xNum*width*xScale;
	(*finalY) = y+yNum*height*yScale;
}

void InvSlot::UpdateDrawCoords(int width, int height) {
	int x;
	int looping = 1;
	int forcestop = 0;
	double y,z;
	if(width!=prevwidth) { // if width has changed
		int xStart = (width-(SpriteDim[0][0]+SpriteDim[2][0]))/SpriteDim[1][0]-1;
		xStart = (xStart>0)?xStart:1;
		x = xStart;
		while(looping) { // find a matching scale and number of copies of middle segment for widths
			x++; // try all multiples of first dimension
			int xwidth = SpriteDim[0][0]+SpriteDim[1][0]*x+SpriteDim[2][0]; // calculate total width of first row (before scaling)
			y = (xwidth-(SpriteDim[5][0]+SpriteDim[3][0]))/((double)SpriteDim[4][0]); // calculate needed number of repetitions of other rows to match up
			z = (xwidth-(SpriteDim[8][0]+SpriteDim[6][0]))/((double)SpriteDim[7][0]);
			SpriteScales[0] = (double)width/(double)xwidth; // calculate needed scale
			cout << x << "," << y << "," << z << ":" << SpriteScales[0] << endl;
			if(((y-((double)((int)y))<0.01) && (z-((double)((int)z))<0.01)) || forcestop) { // if whole numbers needed, use this number of multiples
				looping = 0;
				SpriteNums[0] = x;
				SpriteNums[1] = (int)y;
				SpriteNums[2] = (int)z;
			} else if(SpriteScales[0] < 0.01) {
				forcestop = 1;
				x = xStart;
			}
		}
		prevwidth = width;
		cout << "InvSlot widths changed to: scale=" << SpriteScales[0] << " " << SpriteNums[0] << ":" << SpriteNums[1] << ":" << SpriteNums[2] << " total: " << width << endl;
	}
	looping = 1;
	forcestop = 0;
	if(height!=prevheight) { // if height has changed
		int xStart = (height-(SpriteDim[0][1]+SpriteDim[6][1]))/SpriteDim[3][1]-1;
		xStart = (xStart>0)?xStart:1;
		x = xStart;
		while(looping) { // find a matching scale and number of copies of middle segment for heights
			x++; // try all multiples of first dimension
			int xheight = SpriteDim[0][1]+SpriteDim[3][1]*x+SpriteDim[6][1]; // calculate total height of first column (before scaling)
			y = (xheight-(SpriteDim[7][1]+SpriteDim[1][1]))/((double)SpriteDim[4][1]); // calculate needed number of repetitions of other columns to match up
			z = (xheight-(SpriteDim[8][1]+SpriteDim[2][1]))/((double)SpriteDim[5][1]);
			SpriteScales[1] = (double)height/(double)xheight; // calculate needed scale
			if(((y-((double)((int)y))<0.01) && (z-((double)((int)z))<0.01)) || forcestop) { // if whole numbers needed, use this number of multiples
				looping = 0;
				SpriteNums[3] = x;
				SpriteNums[4] = (int)y;
				SpriteNums[5] = (int)z;
			} else if(SpriteScales[1] < 0.01) {
				forcestop = 1;
				x = xStart;
			}
		}
		prevheight = height;
		cout << "InvSlot heights changed to: scale=" << SpriteScales[1] << " " << SpriteNums[3] << ":" << SpriteNums[4] << ":" << SpriteNums[5] << " total: " << height << endl;
	}
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

ostream& operator<<(ostream& output, const InvSlot Slot) {
	if(Slot.ItemType) {
		output << *(Slot.ItemType) << ": " << Slot.count << "/" << Slot.maxCount;
	} else {
		output << "Empty: " << Slot.count << "/" << Slot.maxCount;
	}
	return output;
}