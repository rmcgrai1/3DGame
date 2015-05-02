// Terrain.h
// Ryan McGrail

#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include "../Primitives/Drawable.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Graphics/TextureController.h"
#include "Heightmap.h"
#include "Water.h"
using namespace std;


class Terrain : public Drawable2 {
	public:
		Terrain(int,int, float, string, float);				// Constructor

		void update(GraphicsOGL*, float);					// Updating
		void draw(GraphicsOGL*, float);						// Drawing
		void drawFirst(GraphicsOGL*, float);				// Things to Draw Before Anything Else
		void drawLast(GraphicsOGL*, float);					// Things to Draw After Everything Else

		float getSeaLevel();								// Getting Sealevel Height
		Heightmap* getHeightmap();							// Getting Heightmap Object

	private:
		int width;											// Width of Terrain
		int height;											// Height of Terrain
		float seaLevel;										// Sealevel Height

		Heightmap* heightmap;								// Heightmap Object
		Water* water;										// Water Object
};

#endif
