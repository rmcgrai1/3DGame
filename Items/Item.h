// Item.h


#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
using namespace std;

class Item : public Physical {
	public:
		~Item();
		
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		
	protected:
		Item();

		int type;
		string* name;
		string* description;
}

#endif
