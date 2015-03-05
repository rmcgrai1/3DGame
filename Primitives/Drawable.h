// Drawable.h

														|

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
		Drawable2(int);

		static deque<Drawable2*> drawableList;

		static int TYPE_NONE;
		static int TYPE_ENVIRONMENT;
		static int TYPE_OBJECT;
		static int TYPE_HUD;
};

#endif
