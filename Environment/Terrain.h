// Terrain.h


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
		Terrain(int,int, float, string, float);

		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
		void drawFirst(GraphicsOGL*, float);
		void drawLast(GraphicsOGL*, float);

		float getSeaLevel();
		Heightmap* getHeightmap();

	private:
		int width;
		int height;
		float seaLevel;

		Heightmap* heightmap;
		Water* water;
};

#endif
