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
		map<string, string> Properties;
		map<string, Texture *> TextureProperties;
		map<string, double *> numProperties;
		map<string, int> PropertyLength;
		map<string, int> Set_TextureProperties;
		map<string, int> Set_numProperties;
		TexturePack *Textures;
		string WorkingDir;
};

#endif