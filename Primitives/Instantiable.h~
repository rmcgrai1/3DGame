// Instantiable.h


#ifndef INSTANTIABLE_H
#define INSTANTIABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"

class GraphicsOGL;
class Instantiable : public Drawable {
	public:
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);

	protected:
		Instantiable();
			
		static deque<Instantiable> instanceList;
};

#endif
