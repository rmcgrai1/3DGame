#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include <iomanip>
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"
#include "../Graphics/models/Model.h"
#include "PosSpec.h"

using namespace std;
class Item {
	friend ostream& operator<<(ostream&, const Item);
	public:
		Item(string newName = "empty", TexturePack *TP = new TexturePack); // constructor
		Item(string newName, string ModelLoc, TexturePack *TP); // constructor - TextureLoc is filename without extension for the file
		Item(string newName, string ModelLoc, string Descrip, TexturePack *TP); // constructor
		void DisplayAt(GraphicsOGL* gl, PosSpec *Dim, double rot);
		void SetName(string newType);
		string GetName();
	private:
		string Name;
		string Description;
		Model *Mod;
		string ModelLocation;
};

#endif