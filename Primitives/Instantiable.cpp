// Instantiable.cpp



#include "../Graphics/GraphicsOGL.h"
#include "Drawable.h"
#include "Instantiable.h"


Instantiable :: Instantiable() : Drawable() {	
}

void Instantiable :: update(GraphicsOGL* gl, float deltaTime) {
	Drawable :: update(gl, deltaTime);
}
void Instantiable :: draw(GraphicsOGL* gl, float deltaTime) {
	Drawable :: draw(gl, deltaTime);
}
