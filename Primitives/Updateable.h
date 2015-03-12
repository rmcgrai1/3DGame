// Updateable.h


#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"

class GraphicsOGL;
class Updateable {
	public:
		static void updateAll(GraphicsOGL*, float);
		virtual void update(GraphicsOGL*, float);

	protected:
		Updateable();

		static deque<Updateable*> updateableList;
};

#endif
