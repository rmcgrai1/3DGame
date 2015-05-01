// Updateable.h
// Ryan McGrail

#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"

class GraphicsOGL;
class Updateable {
	public:
		static void updateAll(GraphicsOGL*, float);		// Updating All Objects
		virtual void update(GraphicsOGL*, float);		// Updating
		virtual void destroy();							// Destroying Object
		static void removeDestroyed();					// Removing Destroyed Works

	protected:
		Updateable();									// Constructor
		Updateable(int);								// Constructor w/ Type

		int oType;

		static deque<Updateable*> updateableList;		// List of Updatable Objects
		static deque<Updateable*> removeUList;			// List of Objects to be Removed

		static const int TYPE_NONE = -1;				// Null Type
		static const int TYPE_MENU = 0;					// Menu Type

		bool doUpdates;									// Should Object be Updated?
};

#endif
