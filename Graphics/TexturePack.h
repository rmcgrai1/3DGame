//TexturePack class:
//to use:
//	create a pointer to a new TexturePack:
//		TexturePack *TP = new TexturePack("Resources");
//	To add a texture (or retrieve a previously added one) and store pointer to the texture in a variable:
//		Texture * SandTexture = TP->newTexture("Images/sand.png", 0);
//	The syntax for adding a texture is very similar to that of the constructor of the Texture class
//	The above function is the equivalent to the code:
//		Texture * SandTexture = new Texture("Resources/Images/sand.png", 0);
//	The folder which the images are loaded from can be changed with the function:
//		TP->ChangeFolder("TexturePacks/DifferentTexturePack");

#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H

#include<iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "../Graphics/Texture.h"
#include "../menus/PosSpec.h"

using namespace std;
class TexturePack {
	public:
		TexturePack(string Folder = "Resources"); // constructor
		Texture *newTexture(const string&, bool);
		PosSpec *newDim(const string&);
		void ChangeFolder(string Folder);
		string GetFolder();
	private:
		PosSpec *loadDim(const string&);
		
		string FolderPath;
		static vector<string> DimFilePaths;
		static map<string, PosSpec*> Dim;
		static map<string, Texture*> Textures;
		static map<string, bool> IsFonts;
		static vector<string> FilePaths;
};

#endif