// Heightmap.h
// Ryan McGrail

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TextureController.h"
using namespace std;

class Controller;
class Heightmap : public Drawable2 {

	public:
		Heightmap(float, float, float);							// Test Constructor
		Heightmap(float, float, float, string);					// Constructor, Heightmap Image

		void draw(GraphicsOGL*, float);							// Drawing

		float getHeightIJ(int, int);							// Get Exact Height at Point
		float getHeightXY(float, float);						// Get Interpolated Point on Map
		void getNormal(float, float, float [3]);				// Get Normal at Interpolated Point
		void getFloorRotations(float, float, float&, float&);	// Get Floor Rotation at Point
	private:
		void setHeight(int, int, float);						// Setting Height at Vertex
		void generateNormals();									// Generate Heightmap Normals

		Texture* texGrass;										// Grass Texture
		Texture* texSand;										// Sand Texture
		Texture* texDirt;										// Dirt Texture
		Image* hmImg;											// Heightmap Image
		void load(string);										// Load Heightmap w/ Filename
		float** heightGrid;										// Grid of Heights
		float*** normGrid;										// Grid of Normals
		float xSize;											// X Size (Width)
		float ySize;											// Y Size (Height)
		int xNum;												// Number of Points along X Axis
		int yNum;												// Number of Points along Y Axis
		float scale;											// xy-scale of Heightamp
};

#endif
