// Drawable.h


#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"

class Drawable : public Updateable {
	public:
		virtual void update(GraphicsOGL, float);
		virtual void draw(GraphicsOGL);

	protected:
		Drawable();
};

#endif
