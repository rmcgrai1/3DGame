// Drawable.h

//														|

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
		static void drawAll(GraphicsOGL*, float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		virtual bool checkOnScreen(GraphicsOGL*);
		bool getOnScreen();

		void setVisible(int);
		void destroy();
		static void removeDestroyed();

	protected:
		Drawable2();
		Drawable2(int);

		int visible;
		bool isOnScreen;

		static int TYPE_NONE;
		static int TYPE_ENVIRONMENT;
		static int TYPE_OBJECT;
		static int TYPE_HUD;

	private:
		static SortedList<Drawable2*> drawableList;
};

#endif
