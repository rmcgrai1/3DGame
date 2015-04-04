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
	return textureMap[name];
}

void TextureController :: initialize() {
	addTexture("Grass","Resources/Images/grass.png");
	addTexture("Sand","Resources/Images/sand.png");
	addTexture("Noise","Resources/Images/noise.png");
	addTexture("Shadow","Resources/Images/shadow.png");
	addTexture("pineBranch","Resources/Images/pineBranch.jpg");
	addTexture("bark","Resources/Images/bark1.png");
}
void TextureController :: addTexture(string name, string fileName) {
	textureMap[name] = new Texture(fileName,false);
	numTextures++;

	cout << "Imported texture " << name << " from file " << fileName << "." << endl;
}
