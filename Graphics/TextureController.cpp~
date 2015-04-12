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


int TextureController :: numTextures = 0;
map<string,Texture*> TextureController :: textureMap;

TextureController :: TextureController() {
}
	
Texture* TextureController :: getTexture(string name) {
	return textureMap[name];
}

void TextureController :: initialize() {
	addTexture("Grass","Resources/Images/grass.png");
	addTexture("Sand","Resources/Images/sand.png");
	addTexture("Noise","Resources/Images/noise.png");
	addTexture("Shadow","Resources/Images/shadow.png");
	addTexture("pineBranch","Resources/Images/pineBranch.png");
	addTexture("bark","Resources/Images/bark1.png");
	addTexture("Dirt","Resources/Images/dirt.png");
	addTexture("Heart0","Resources/Images/heart0.png");
	addTexture("Heart1","Resources/Images/heart1.png");
	addTexture("Heart2","Resources/Images/heart2.png");
	addTexture("Heart3","Resources/Images/heart3.png");
	addTexture("Heart4","Resources/Images/heart4.png");
}
void TextureController :: addTexture(string name, string fileName) {
	textureMap[name] = new Texture(fileName,false);
	numTextures++;

	cout << "Imported texture " << name << " from file " << fileName << "." << endl;
}
