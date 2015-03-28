// Hud.cpp

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

Hud :: Hud() : Drawable2() {
	isDisplaying = true;
}

void Hud :: update(GraphicsOGL* gl, float deltaT) {
}
void Hud :: draw(GraphicsOGL* gl, float deltaT) {
	if(isDisplaying) {
	}
}

bool Hud :: getDisplaying() {
	return isDisplaying;
}