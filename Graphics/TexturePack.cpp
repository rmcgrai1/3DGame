#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include "../Graphics/Texture.h"

#include "TexturePack.h"
using namespace std;
//FileIO *TexturePack::fileinput;
vector<string> TexturePack::DimFilePaths;
map<string, int*> TexturePack::Dim;
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

int *TexturePack::newDim(const string& filePath) {
	cout << filePath << ": ";
	int *ThisDim = Dim[filePath]; // get the dimensions for the specified filename (should be NULL if not loaded)
	if(ThisDim) { // already loaded
		cout << "Already loaded!\n";
		return ThisDim;
	} else { // not yet loaded
		DimFilePaths.push_back(filePath);
		string fileName = FolderPath + "/" + filePath;
		ThisDim = loadDim(fileName);
		Dim[filePath] = ThisDim;
		cout << Dim[filePath][0] << "x" << Dim[filePath][1] << endl;
		return ThisDim;
	}
}

void TexturePack::ChangeFolder(string Folder) {
	FolderPath = Folder;
	//Reload textures
	vector<string>::iterator ThisPath;
	for(ThisPath = FilePaths.begin(); ThisPath != FilePaths.end(); ++ThisPath) {
		string filePath = (*ThisPath);
		cout << filePath << ": ";
		delete Textures[filePath];
		string fileName = FolderPath + "/" + filePath;
		Textures[filePath] = new Texture(fileName, IsFonts[filePath]);
	}
	//Reload dimensions
	for(ThisPath = DimFilePaths.begin(); ThisPath != DimFilePaths.end(); ++ThisPath) {
		string filePath = (*ThisPath);
		cout << filePath << ": ";
		string fileName = FolderPath + "/" + filePath;
		delete Dim[filePath];
		Dim[filePath] = loadDim(fileName);
		cout << Dim[filePath][0] << "x" << Dim[filePath][1] << endl;
	}
	
}

string TexturePack::GetFolder() {
	return FolderPath;
}

int *TexturePack::loadDim(const string& fileName) {
	ifstream dimfile;
	dimfile.open(fileName.c_str());
	char digit[1];
	vector<int> values;
	if(dimfile.is_open()) { // if file not opened, skip loading of contents (will default to 1x1)
	dimfile.read(digit, 1);
		while(!dimfile.eof()) {
			int thisval = 0;
			while(!dimfile.eof() && isdigit(digit[0])) {
				thisval*=10;
				thisval+=(digit[0]-'0');
				dimfile.read(digit, 1);
			}
			dimfile.read(digit, 1);
			values.push_back(thisval);
		}
		dimfile.close();
	}
	int size = values.size();
	size = (size>1)?size:2; // make sure at least 2 elements
	int *dims = new int[size];
	int i;
	for(i=size-1;i>=0;i--) {
		if(values.size()) { // if there isn't a value for this dimension, set value to 1
			dims[i] = values.back();
			values.pop_back();
		} else {
			dims[i] = 1;
		}
	}
	return dims;
}