// TextureController.h


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
		static void initialize();
		static Texture* getTexture(string);

	private:
		TextureController();
		static void addTexture(string,string);
		static map<string, Texture*> textureMap;
		static int numTextures;
};

#endif
