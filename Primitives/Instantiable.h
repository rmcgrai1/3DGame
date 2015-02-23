// Instantiable.h


#ifndef INSTANTIABLE_H
#define INSTANTIABLE_H

#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"

class Instantiable : public Drawable {
	public:
		virtual void update(GraphicsOGL, float);
		virtual void draw(GraphicsOGL);

	protected:
		Instantiable();
};

#endif
