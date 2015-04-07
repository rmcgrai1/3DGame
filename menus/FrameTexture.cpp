#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include "../Graphics/Texture.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/GraphicsOGL.h"
#include "PosSpec.h"

#include "FrameTexture.h"
using namespace std;
FrameTexture::FrameTexture(TexturePack *TP, string Folder) {
	Textures = TP;
	FrameFolder = Folder;
	
	prevheight = 0;
	prevwidth = 0;
	int i;
	for(i=0;i<9;i++) {
		SpriteDim[i] = Textures->newDim(FrameFolder + "/" + to_string(i) + ".dim"); // load each of these dimensions from a different file, and the texture from a different file
		Sprites[i] = Textures->newTexture(FrameFolder + "/" + to_string(i) + ".png", false);
	}
}

void FrameTexture::drawat(GraphicsOGL* gl, PosSpec *Dim, PosSpec *inCoords) {
	UpdateDrawCoords(Dim->getWidth(), Dim->getHeight());
	int x = Dim->getLeftX();
	int y = Dim->getTopY();
	int x2 = Dim->getRightX();
	int y2 = Dim->getBottomY();
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
		if(i==4 && inCoords) {
			int itemwidth = SpriteDim[4]->getWidth()*xNum*SpriteScales[0];
			int itemheight = SpriteDim[4]->getHeight()*yNum*SpriteScales[1];
			inCoords->setTopLeft(curX,curY[1]); // MAY BE INCORRECT INDEX OF curY
			inCoords->changeDim(itemwidth,itemheight);
		}
		tileTexture(gl,curX,curY[i%3],SpriteDim[i]->getWidth(),SpriteDim[i]->getHeight(),xNum,yNum,SpriteScales[0],SpriteScales[1],&curX,&curY[i%3],Sprites[i]);
		
	}
}

void FrameTexture::tileTexture(GraphicsOGL* gl, int x, int y, int width, int height, int xNum, int yNum, double xScale, double yScale, int *finalX, int *finalY, Texture* Tex) {
	int i,j;
	for(i=0;i<xNum;i++) {
		for(j=0;j<yNum;j++) {
			if(gl) { // don't draw if gl is NULL
				gl->drawTextureScaled(x+i*width*xScale, y+j*height*yScale, xScale, yScale, Tex);
			}
		}
	}
	(*finalX) = x+xNum*width*xScale;
	(*finalY) = y+yNum*height*yScale;
}

void FrameTexture::UpdateDrawCoords(int width, int height) {
	if(!width) {
		width = 10;
	}
	if(!height) {
		height = 10;
	}
	int x;
	int looping = 1;
	int forcestop = 0;
	double y,z;
	if(width!=prevwidth) { // if width has changed
		int xStart = (width-(SpriteDim[0]->getWidth()+SpriteDim[2]->getWidth()))/SpriteDim[1]->getWidth()-1;
		xStart = (xStart>0)?xStart:1;
		x = xStart;
		while(looping) { // find a matching scale and number of copies of middle segment for widths
			x++; // try all multiples of first dimension
			int xwidth = SpriteDim[0]->getWidth()+SpriteDim[1]->getWidth()*x+SpriteDim[2]->getWidth(); // calculate total width of first row (before scaling)
			y = (xwidth-(SpriteDim[5]->getWidth()+SpriteDim[3]->getWidth()))/((double)SpriteDim[4]->getWidth()); // calculate needed number of repetitions of other rows to match up
			z = (xwidth-(SpriteDim[8]->getWidth()+SpriteDim[6]->getWidth()))/((double)SpriteDim[7]->getWidth());
			SpriteScales[0] = (double)width/(double)xwidth; // calculate needed scale
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
		cout << *SpriteDim[3] << endl;
		int xStart = (height-(SpriteDim[0]->getHeight()+SpriteDim[6]->getHeight()))/SpriteDim[3]->getHeight()-1;
		xStart = (xStart>0)?xStart:1;
		x = xStart;
		while(looping) { // find a matching scale and number of copies of middle segment for heights
			x++; // try all multiples of first dimension
			int xheight = SpriteDim[0]->getHeight()+SpriteDim[3]->getHeight()*x+SpriteDim[6]->getHeight(); // calculate total height of first column (before scaling)
			y = (xheight-(SpriteDim[7]->getHeight()+SpriteDim[1]->getHeight()))/((double)SpriteDim[4]->getHeight()); // calculate needed number of repetitions of other columns to match up
			z = (xheight-(SpriteDim[8]->getHeight()+SpriteDim[2]->getHeight()))/((double)SpriteDim[5]->getHeight());
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