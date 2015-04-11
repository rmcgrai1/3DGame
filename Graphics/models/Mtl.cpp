#include<iostream>
#include <iomanip>
#include <map>
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/Texture.h"

#include "Mtl.h"
map<string, string> Mtl::Properties;
map<string, Texture *> Mtl::TextureProperties;
map<string, double *> Mtl::numProperties;
map<string, int> Mtl::PropertyLength;

using namespace std;
Mtl::Mtl(string Directory, TexturePack *TP) {
	Textures = TP;
	WorkingDir = Directory;
}

void Mtl::InterpretLine(string Line) {
	//TEMPORARY hardcoded options
	Properties["map_Kd"] = "Metal_Brass_Ceiling.png";
	TextureProperties["map_Kd"] = Textures->newTexture("Images/Items/dirt.png", 0);//Textures->newTexture(WorkingDir + "/" + "Metal_Brass_Ceiling.png", 0);
	numProperties["map_Kd"] = new double[1];
	numProperties["map_Kd"][0] = 0.0;
	PropertyLength["map_Kd"] = 0;
	cout << TextureProperties["map_Kd"] << endl;
	//TEMPORARY hardcoded options (end)
}

string Mtl::getProperty(string Property) {
	return Properties[Property];
}

Texture *Mtl::getTexture(string Property) {
	return TextureProperties[Property];
}

double *Mtl::getNumProperty(string Property) {
	return numProperties[Property];
}

int Mtl::getPropertyLength(string Property) {
	return PropertyLength[Property];
}