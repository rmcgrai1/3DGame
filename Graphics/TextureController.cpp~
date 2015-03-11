// TextureController.cpp

#include <iostream>
#include <string>
#include <map>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Texture.h"
#include "TextureController.h"
using namespace std;


TextureController :: TextureController() {
	numTextures = 0;

	initialize();
}
	
Texture* TextureController :: getTexture(string name) {
	cout << "What" << endl;
	cout << numTextures << endl;
	return textureMap[name];
}

void TextureController :: initialize() {
	addTexture("Grass","Resources/Images/grass.png");
	addTexture("Sand","Resources/Images/sand.png");
	addTexture("Noise","Resources/Images/noise.png");
}
void TextureController :: addTexture(string name, string fileName) {
	textureMap[name] = new Texture(fileName,false);
	numTextures++;

	cout << "Imported texture " << name << " from file " << fileName << "." << endl;
}
