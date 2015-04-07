#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <deque>
#include <map>
#include "../Graphics/Texture.h"
#include "../menus/PosSpec.h"

#include "TexturePack.h"
using namespace std;
//FileIO *TexturePack::fileinput;
vector<string> TexturePack::DimFilePaths;
map<string, PosSpec*> TexturePack::Dim;
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

PosSpec *TexturePack::newDim(const string& filePath) {
	cout << filePath << ": ";
	PosSpec *ThisDim = Dim[filePath]; // get the dimensions for the specified filename (should be NULL if not loaded)
	if(ThisDim) { // already loaded
		cout << "Already loaded!\n";
		return ThisDim;
	} else { // not yet loaded
		DimFilePaths.push_back(filePath);
		string fileName = FolderPath + "/" + filePath;
		ThisDim = loadDim(fileName);
		Dim[filePath] = ThisDim;
		cout << "[" << *(Dim[filePath]) << "]\n";
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
		cout << Dim[filePath]->getWidth() << "x" << Dim[filePath]->getHeight() << endl;
	}
	
}

string TexturePack::GetFolder() {
	return FolderPath;
}

PosSpec *TexturePack::loadDim(const string& fileName) {
	ifstream dimfile;
	dimfile.open(fileName.c_str());
	char digit[1];
	deque<int> values;
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
	/*int size = values.size();
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
	}*/
	PosSpec *dims = new PosSpec;
	if(values.size()) { // if there isn't a value for this dimension, set value to 1
		dims->setWidth(values.front());
		values.pop_front();
	} else {
		dims->setWidth(1);
	}
	if(values.size()) { // if there isn't a value for this dimension, set value to 1
		dims->setHeight(values.front());
		values.pop_front();
	} else {
		dims->setHeight(1);
	}
	if(values.size()) { // if there isn't a value for this dimension, set value to 0
		dims->setTopLeft(values.front(),0);
		values.pop_front();
	} else {
		dims->setTopLeft(0,0);
	}
	if(values.size()) { // if there isn't a value for this dimension, set value to 0
		dims->setTopLeft(dims->getLeftX(),values.front());
		values.pop_front();
	} else {
		dims->setTopLeft(dims->getLeftX(),0);
	}
	return dims;
}