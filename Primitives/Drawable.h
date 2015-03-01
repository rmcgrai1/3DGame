// Drawable.h


#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"

class GraphicsOGL;
class Drawable2 : public Updateable {
	public:
		static void drawAll(GraphicsOGL*, float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

	protected:
		Drawable2();

		static deque<Drawable2*> drawableList;
};

#endif
