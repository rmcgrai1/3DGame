#include<iostream>
#include <iomanip>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"
#include "PosSpec.h"

#include "item.h"
using namespace std;
Item::Item(string newName, TexturePack *TP) {
	Name = newName;
	Description = "";
	TextureLocation = "Images/Items/Blank.png";
	//DimLocation = "Images/Items/Blank.dim";
	Tex = TP->newTexture(TextureLocation, false);
	//Dim = TP->newDim(DimLocation);
}

Item::Item(string newName, string TextureLoc, TexturePack *TP) {
	Name = newName;
	Description = "";
	TextureLocation = TextureLoc + ".png";
	//DimLocation = TextureLoc + ".dim";
	Tex = TP->newTexture(TextureLocation, false);
	//Dim = TP->newDim(DimLocation);
}

Item::Item(string newName, string TextureLoc, string Descrip, TexturePack *TP) {
	Name = newName;
	Description = Descrip;
	TextureLocation = TextureLoc + ".png";
	//DimLocation = TextureLoc + ".dim";
	Tex = TP->newTexture(TextureLocation, false);
	//Dim = TP->newDim(DimLocation);
}

void Item::DisplayAt(GraphicsOGL* gl, PosSpec *Dim, double rot) {
	gl->transformClear();
	gl->transformTranslation(Dim->getCenterX(),Dim->getCenterY(),100);
	gl->transformRotationX(-135);
	gl->transformRotationZ(rot);
	gl->transformScale(0.5);
	gl->transformTranslation(0,0,Dim->getHeight()/-2);
	gl->draw3DPrism(0, 0, 0, Dim->getWidth(), Dim->getHeight(), 4, Tex);
	gl->transformClear();
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