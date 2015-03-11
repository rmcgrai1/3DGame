#include<iostream>
#include <iomanip>
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "item.h"
using namespace std;
Item::Item(string newType) {
	Type = newType;
}

void Item::SetType(string newType) {
	Type = newType;
}

string Item::GetType() {
	return Type;
}

ostream& operator<<(ostream& output, const Item item) {
	output << item.Type;
	return output;
}