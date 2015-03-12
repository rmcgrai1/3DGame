// Terrain.cpp



#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TextureController.h"
#include "Heightmap.h"
#include "Terrain.h"
#include "Water.h"
#include "../Primitives/Drawable.h"
using namespace std;


Terrain :: Terrain(TextureController* tc, int w, int h, string hmFileName, float newSeaLevel)  {

	width = w;
	height = h;
	seaLevel = newSeaLevel;
	
	heightmap = new Heightmap(tc, w, h, hmFileName);
		heightmap->setVisible(false);
	water = new Water(w,h,newSeaLevel);
		water->setVisible(false);
}
	
void Terrain :: update(GraphicsOGL* gl, float deltaTime) {
}

void Terrain :: draw(GraphicsOGL* gl, float deltaTime) {
}

void Terrain :: drawFirst(GraphicsOGL* gl, float deltaTime) {
	heightmap->draw(gl,deltaTime);
}

void Terrain :: drawLast(GraphicsOGL* gl, float deltaTime) {
	water->draw(gl,deltaTime);
}

float Terrain :: getSeaLevel() {
	return seaLevel;
}

Heightmap* Terrain :: getHeightmap() {
	return heightmap;
}

