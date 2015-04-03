// Terrain.cpp



#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TextureController.h"
#include "Heightmap.h"
#include "Terrain.h"
#include "Water.h"
#include "../Primitives/Drawable.h"
using namespace std;


Terrain :: Terrain(TextureController* tc, int w, int h, float zH, string hmFileName, float newSeaLevel)  {

	width = w;
	height = h;
	seaLevel = newSeaLevel;
	
	heightmap = new Heightmap(tc, w, h, zH, hmFileName);
		heightmap->setVisible(false);
	water = new Water(w,h,newSeaLevel);
		water->setVisible(false);
}
	
void Terrain :: update(GraphicsOGL* gl, float deltaTime) {
}

void Terrain :: draw(GraphicsOGL* gl, float deltaTime) {
}

void Terrain :: drawFirst(GraphicsOGL* gl, float deltaTime) {
	// Draw Sky
	Player* p;
	p = gl->getPlayer();

	gl->enableShader("Sky");
		gl->transformTranslation(p->getX(),p->getY(),p->getZ());

		float sc = 2000;

		gl->draw3DFloor(-sc,-sc,sc,sc,sc);
		gl->draw3DWall(-sc,-sc,sc,sc,-sc,-sc);
		gl->draw3DWall(-sc,sc,sc,sc,sc,-sc);
		gl->draw3DWall(-sc,-sc,sc,-sc,sc,-sc);
		gl->draw3DWall(sc,-sc,sc,sc,sc,-sc);
		gl->transformClear();
	gl->disableShaders();



	gl->logMessage("Terrain.cpp, drawFirst()");
	heightmap->draw(gl,deltaTime);
}

void Terrain :: drawLast(GraphicsOGL* gl, float deltaTime) {

	gl->logMessage("Terrain.cpp, drawLast()");
	water->draw(gl,deltaTime);
}

float Terrain :: getSeaLevel() {
	return seaLevel;
}

Heightmap* Terrain :: getHeightmap() {
	return heightmap;
}

