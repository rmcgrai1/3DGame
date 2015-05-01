// Drawable.h
// Ryan McGrail

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "Updateable.h"
#include "../Data/SortedList.h"

class Heightmap;
class GraphicsOGL;
class Drawable2 : public Updateable {
	public:
		static void drawAll(GraphicsOGL*, float);		// Drawing All Objects
		virtual void update(GraphicsOGL*, float);		// Updating
		virtual void draw(GraphicsOGL*, float);			// Drawing
		virtual bool checkOnScreen(GraphicsOGL*);		// Check if Onscreen
		bool getOnScreen();								// Get if Onscreen

		void setVisible(int);							// Set Visibility
		void destroy();									// Destroy Object
		static void removeDestroyed();					// Remove Destroyed Objects

	protected:
		Drawable2();									// Constructor
		Drawable2(int);									// Constructor w/ Type

		int visible;									// Should Draw?
		bool isOnScreen;								// Is Object Onscreen?
		float fidelity;									// Drawing Fidelity (Decreases w/ Distance)

		static int TYPE_NONE;							// Null Type
		static int TYPE_ENVIRONMENT;					// Environment Type
		static int TYPE_OBJECT;							// Object Type
		static int TYPE_HUD;							// Hud Type

	private:
		static SortedList<Drawable2*> drawableList;		// List of Drawable Objects
};

#endif
