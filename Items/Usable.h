// Usable.h


#ifndef USABLE_H
#define USABLE_H

#include "../Graphics/GraphicsOGL.h"
#include "Item.h"


class Useable : public Usable {

	public:
		~Usable();
		
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

		void use();
	
	protected:
		Usable();
}

#endif
