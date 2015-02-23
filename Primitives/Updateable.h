// Updateable.h


#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "../Graphics/GraphicsOGL.h"

class Updateable {
	public:
		virtual void update(GraphicsOGL, float);

	protected:
		Updateable();
};

#endif
