// Instantiable.h
// Ryan McGrail

// The Instantiable class is for anything that can be instantiated in multiples. It is not meant for any 
// important resource controllers, though it does include the player (which will tend to only exist alone). The
// general rule of thumb is that if its data is not CRITICAL, and it is safe to be destroyed, then it can be of
// type Instantiable. In fact, anything destructible SHOULD be of type Instantiable.

#ifndef INSTANTIABLE_H
#define INSTANTIABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"

class GraphicsOGL;
class Instantiable : public Drawable2 {
	public:
		virtual void update(GraphicsOGL*, float);					// Updating
		virtual void draw(GraphicsOGL*, float);						// Drawing

		void destroy();												// Destroy
		static void removeDestroyed();								// Remove Destroyed Objects

	protected:
		Instantiable();												// Hidden Constructor (Do Not Instantiate!!)
			
		static deque<Instantiable*> instanceList;					// List of Instances
		static deque<Instantiable*> removeIList;					// List of Objects to Remove
};

#endif
