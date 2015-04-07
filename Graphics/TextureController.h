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
		TextureController();
		Texture* getTexture(string);

	private:
		void initialize();
		void addTexture(string,string);
		map<string, Texture*> textureMap;

		int numTextures;
};

#endif
