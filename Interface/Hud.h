// Hud.h

#ifndef HUD_H
#define HUD_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class Hud : public Drawable2 {
	public:
		Hud();
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
		bool getDisplaying();
		
	private:
		void isDisplaying;
};

#endif