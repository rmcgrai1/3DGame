#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include <iomanip>
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

using namespace std;
class Item {
	friend ostream& operator<<(ostream&, const Item);
	public:
		Item(string newType = "empty"); // constructor: if number is 0, item is always "empty"
		void SetType(string newType);
		string GetType();
	private:
		string Type;
};

#endif