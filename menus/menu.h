#ifndef MENU_H
#define MENU_H

#include<iostream>
#include <iomanip>
#include <vector>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/TexturePack.h"
#include "../Graphics/Texture.h"

#include "item.h"
#include "invslot.h"
#include "playerInv.h"
using namespace std;
class Menu : public Drawable2 {
	friend ostream& operator<<(ostream&, const Menu);
	public:
		Menu(); // constructor
		void draw(GraphicsOGL*, float);
		void update(GraphicsOGL*, float);
		int getMenuShowStatus(); // returns whether any menu is being shown (may be needed for pausing execution of game, etc.)
		void updateDrawCoords(GraphicsOGL*);
	private:
		playerInv *playerInventory;
		
		TexturePack *Textures;
		
		Texture *Cursor;
		
		int ShowMenu;
		int mouseX;
		int mouseY;
		
		int scrwidth,scrheight;
		int leftx,topy;
		int invwidth,invheight;
		static double ItemRot;
};

#endif
