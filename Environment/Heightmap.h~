// Heightmap.h

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"

class GraphicsOGL;
class Heightmap : public Drawable {
	public:
		Heightmap(float, float, float);
		Heightmap(float, float, int**);
		Heightmap(float, float, float**);

		void draw(GraphicsOGL*, float);

		float getHeightIJ(int, int);
		float getHeightXY(float, float);
		void getNormal(float, float, float*);
		bool isFloor(float, float);
		bool isWall(float, float);
	private:
		void setHeight(int, int, float);

		void load(string);
		float** heightGrid;
		float xSize;
		float ySize;
		int xNum;
		int yNum;
		float scale;
};

#endif
