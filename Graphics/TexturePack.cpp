#include<iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "../Graphics/Texture.h"

#include "TexturePack.h"
using namespace std;
vector<string> TexturePack::FilePaths;
map<string, Texture*> TexturePack::Textures;
map<string, bool> TexturePack::IsFonts;
TexturePack::TexturePack(string Folder) {
	FolderPath = Folder;
}

Texture *TexturePack::newTexture(const string& filePath, bool isFont) {
	cout << filePath << ": ";
	Texture *ThisTexture = Textures[filePath]; // get the texture for the specified filename (should be NULL if not loaded)
	if(ThisTexture) { // already loaded
		cout << "Already loaded!\n";
		return Textures[filePath];
	} else { // not yet loaded
		FilePaths.push_back(filePath);
		string fileName = FolderPath + "/" + filePath;
		ThisTexture = new Texture(fileName, isFont);
		Textures[filePath] = ThisTexture;
		IsFonts[filePath] = isFont;
		return ThisTexture;
	}
}

void TexturePack::ChangeFolder(string Folder) {
	FolderPath = Folder;
	vector<string>::iterator ThisPath;
	for(ThisPath = FilePaths.begin(); ThisPath != FilePaths.end(); ++ThisPath) {
		string filePath = (*ThisPath);
		cout << filePath << ": ";
		delete Textures[filePath];
		string fileName = FolderPath + "/" + filePath;
		Textures[filePath] = new Texture(fileName, IsFonts[filePath]);
	}
}

string TexturePack::GetFolder() {
	return FolderPath;
}