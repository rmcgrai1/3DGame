#ifndef MTL_H
#define MTL_H

#include<iostream>
#include <iomanip>
#include <map>
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/Texture.h"

using namespace std;
class Mtl {
	public:
		Mtl(string Directory = "Models/default", TexturePack *TP = new TexturePack);
		void InterpretLine(string Line);
		string getProperty(string Property);
		Texture *getTexture(string Property);
		double *getNumProperty(string Property);
		int getPropertyLength(string Property);
	private:
		/*static */map<string, string> Properties;
		/*static */map<string, Texture *> TextureProperties;
		/*static */map<string, double *> numProperties;
		/*static */map<string, int> PropertyLength;
		TexturePack *Textures;
		string WorkingDir;
};

#endif