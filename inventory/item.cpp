#include<iostream>
#include <iomanip>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "item.h"
using namespace std;
Item::Item(string newName, TexturePack *TP) {
	Name = newName;
	Description = "";
	TextureLocation = "Images/Items/Blank.png";
	DimLocation = "Images/Items/Blank.dim";
	Tex = TP->newTexture(TextureLocation, false);
	Dim = TP->newDim(DimLocation);
}

Item::Item(string newName, string TextureLoc, TexturePack *TP) {
	Name = newName;
	Description = "";
	TextureLocation = TextureLoc + ".png";
	DimLocation = TextureLoc + ".dim";
	Tex = TP->newTexture(TextureLocation, false);
	Dim = TP->newDim(DimLocation);
}

Item::Item(string newName, string TextureLoc, string Descrip, TexturePack *TP) {
	Name = newName;
	Description = Descrip;
	TextureLocation = TextureLoc + ".png";
	DimLocation = TextureLoc + ".dim";
	Tex = TP->newTexture(TextureLocation, false);
	Dim = TP->newDim(DimLocation);
}

void Item::DisplayAt(GraphicsOGL* gl, int x, int y, int width, int height) {
	gl->drawTextureScaled(x, y, width/((double)Dim[0]), height/((double)Dim[1]), Tex);
}

void Item::SetName(string newName) {
	Name = newName;
}

string Item::GetName() {
	return Name;
}

ostream& operator<<(ostream& output, const Item item) {
	output << item.Name;
	return output;
}