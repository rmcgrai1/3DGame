#ifndef FRAMETEXTURE_H
#define FRAMETEXTURE_H

#include<iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "../Graphics/Texture.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/GraphicsOGL.h"

using namespace std;
class FrameTexture {
	public:
		FrameTexture(TexturePack *TP = new TexturePack, string Folder = "Images/Inventory/BlankSlot"); // constructor
		void drawat(GraphicsOGL* gl, int x, int y, int x2, int y2, int *inCoords); // draws the frame at this position and stores the coordinates of the inside in inCoords array
		void tileTexture(GraphicsOGL* gl, int x, int y, int width, int height, int xNum, int yNum, double xScale, double yScale, int *finalX, int *finalY, Texture* Tex); // tiles a texture at a position, with specified scale a specified numbert of times
		void UpdateDrawCoords(int width, int height);
	private:
		TexturePack *Textures;
		string FrameFolder;
		
		int prevwidth;
		int prevheight;
		double SpriteScales[2];
		int SpriteNums[6];
		int *SpriteDim[9];
		Texture *Sprites[9];
};

#endif
