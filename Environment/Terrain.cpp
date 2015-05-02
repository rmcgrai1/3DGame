// Terrain.cpp
// Ryan McGrail


#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TextureController.h"
#include "Heightmap.h"
#include "Terrain.h"
#include "Water.h"
#include "../Primitives/Drawable.h"
using namespace std;


// Constructor
Terrain :: Terrain(int w, int h, float zH, string hmFileName, float newSeaLevel)  {

	// Set Width, Height, and Sealevel
	width = w;
	height = h;
	seaLevel = newSeaLevel;
	
	// Create Heightmap, Disable Automatic Drawing
	heightmap = new Heightmap(w, h, zH, hmFileName);
		heightmap->setVisible(false);
	// Create Water, Disable Automatic Drawing
	water = new Water(w,h,newSeaLevel);
		water->setVisible(false);
}
	
// Updating
void Terrain :: update(GraphicsOGL* gl, float deltaTime) {
}

// Drawing
void Terrain :: draw(GraphicsOGL* gl, float deltaTime) {
}

// First things to Draw
void Terrain :: drawFirst(GraphicsOGL* gl, float deltaTime) {
	// Draw Sky
	Player* p;
	p = gl->getPlayer();

	// Cloud Texture (Noise)
	Texture* cloudTex = TextureController::getTexture("Noise");

	// If PC Not Too Slow, Draw Skybox
	if(!gl->isPCSlow())
		// Enable Sky Texture (This is where "Magic" Happens)
		gl->enableShader("Sky");
		
		// Bind Cloud Texture
		cloudTex->bind();
		
		// Move to Player Position
		gl->transformTranslation(p->getX(),p->getY(),p->getZ());

		// Draw Box Around Player
		float sc = 2000;
		gl->draw3DFloor(-sc,-sc,sc,sc,sc);
		gl->draw3DWall(-sc,-sc,sc,sc,-sc,-sc);
		gl->draw3DWall(-sc,sc,sc,sc,sc,-sc);
		gl->draw3DWall(-sc,-sc,sc,-sc,sc,-sc);
		gl->draw3DWall(sc,-sc,sc,sc,sc,-sc);
		gl->transformClear();

		// Unbind Cloud Texture
		cloudTex->unbind();
	gl->disableShaders();

	// Draw Terrain, 
	heightmap->draw(gl,deltaTime);
}

// Final things to Draw
void Terrain :: drawLast(GraphicsOGL* gl, float deltaTime) {
	
	// Draw Terrain Last, So it Doesn't Block Others
	water->draw(gl,deltaTime);
}

float Terrain :: getSeaLevel() {
	return seaLevel;
}

Heightmap* Terrain :: getHeightmap() {
	return heightmap;
}

