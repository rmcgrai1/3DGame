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
	ModelLocation = "Resources/Models/default";
	Mod = new Model(ModelLocation,TP);
}

Item::Item(string newName, string ModelLoc, TexturePack *TP) {
	Name = newName;
	Description = "";
	ModelLocation = ModelLoc;
	Mod = new Model(ModelLocation,TP);
}

Item::Item(string newName, string ModelLoc, string Descrip, TexturePack *TP) {
	Name = newName;
	Description = Descrip;
	ModelLocation = ModelLoc;
	Mod = new Model(ModelLocation,TP);
}

void Item::DisplayAt(GraphicsOGL* gl, PosSpec *Dim, double rot) {
	gl->transformClear();
	gl->transformTranslation(Dim->getCenterX(),Dim->getCenterY(),100);
	gl->transformRotationX(-135);
	gl->transformRotationZ(rot);
	//gl->transformScale(0.5);
	gl->transformScale(Dim->getWidth()/2);
	//gl->transformTranslation(0,0,Dim->getHeight()/-2);
	//gl->draw3DPrism(0, 0, 0, Dim->getWidth(), Dim->getHeight(), 4, Tex);
	gl->draw3DModel(Mod);
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