// TextureController.h
// Ryan McGrail

#ifndef TEXTURECONTROLLER_H
#define TEXTURECONTROLLER_H

#include <string>
#include <map>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"

using namespace std;

class TextureController {
	public:
		static void initialize();							// Initialize Textures
		static Texture* getTexture(string);					// Get Texture

	private:
		TextureController();								// Constructor (This Should NOT be Instantiated!)
		static void addTexture(string,string);				// Add Texture
		static map<string, Texture*> textureMap;			// Texture Map
		static int numTextures;								// Number of Textures
};

#endif
