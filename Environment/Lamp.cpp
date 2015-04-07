// Lamp.h


#include "../Primitives/Physical.h"
#include "../Graphics/GraphicsOGL.h"

Lamp :: Lamp(float x, float y, float z) : Physical(x,y,z) {
	height = 0;
	rotate = 0;
}

void Lamp :: update(GraphicsOGL* gl, float deltaTime) {
	rotate += 3*deltaTime;
}
void Lamp :: draw(GraphicsOGL* gl, float deltaTime) {
	gl->draw3DBlock();
}

