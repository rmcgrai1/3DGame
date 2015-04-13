#include<iostream>
#include <iomanip>
#include <map>
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/Texture.h"

#include "Mtl.h"
/*map<string, string> Mtl::Properties;
map<string, Texture *> Mtl::TextureProperties;
map<string, double *> Mtl::numProperties;
map<string, int> Mtl::PropertyLength;*/

using namespace std;
Mtl::Mtl(string Directory, TexturePack *TP) {
	Textures = TP;
	WorkingDir = Directory;
}

void Mtl::InterpretLine(string Line) {
	int pos = Line.find(" ");
	string Command = Line.substr(0,pos);
	string Params = Line.substr(pos+1,256);
	Properties[Command] = Params;
	Set_TextureProperties[Command] = 0;
	Set_numProperties[Command] = 0;
	
	
	/*//TEMPORARY hardcoded options
	Properties["map_Kd"] = "Metal_Brass_Ceiling.png";
	TextureProperties["map_Kd"] = Textures->newTexture(WorkingDir + "/" + "Metal_Brass_Ceiling.png", 0);
	numProperties["map_Kd"] = new double[1];
	numProperties["map_Kd"][0] = 0.0;
	PropertyLength["map_Kd"] = 0;
	cout << TextureProperties["map_Kd"] << endl;
	//TEMPORARY hardcoded options (end)*/
}

string Mtl::getProperty(string Property) {
	return Properties[Property];
}

Texture *Mtl::getTexture(string Property) {
	if(Set_TextureProperties[Property]) {
		return TextureProperties[Property];
	} else {
		TextureProperties[Property] = Textures->newTexture(WorkingDir + "/" + Properties[Property], 0);
		
		Set_TextureProperties[Property] = 1;
		return TextureProperties[Property];
	}
}

double *Mtl::getNumProperty(string Property) {
	if(Set_numProperties[Property]) {
		return numProperties[Property];
	} else {
		numProperties[Property] = new double[1];
		numProperties[Property][0] = 0.0;
		PropertyLength[Property] = 0;
		
		Set_numProperties[Property] = 1;
		return numProperties[Property];
	}
}

int Mtl::getPropertyLength(string Property) {
	if(Set_numProperties[Property]) {
		return PropertyLength[Property];
	} else {
		numProperties[Property] = new double[1];
		numProperties[Property][0] = 0.0;
		PropertyLength[Property] = 0;
		
		Set_numProperties[Property] = 1;
		return PropertyLength[Property];
	}
}