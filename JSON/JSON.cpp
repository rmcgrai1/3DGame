// JSON.cpp

#include<iostream>
#include <iomanip>
#include<string>
#include<fstream>
#include <vector>
#include <map>
#include "JSON.h"
#include "JSONvalue.h"

using namespace std;
JSON::JSON(string filename) {
	ifstream File;
	File.open(filename.c_str());
	if(File.is_open()) {
		load(&File);
		File.close();
	} else {
		cout << "Failed to open file \"" << filename << "\" for reading!\n";
	}
}

JSON::JSON(ifstream *FilePtr) {
	load(FilePtr);
}

void JSON::load(ifstream *FilePtr) {
	char thischar = FilePtr->get();
	while(thischar!='{' && !FilePtr->eof()) { // ignore all characters until first '{'
		thischar = FilePtr->get();
	}
	while(!FilePtr->eof() && thischar!='}') {
		JSONvalue *thisnameVal = new JSONvalue(FilePtr);
		if(!thisnameVal->istype("string")) break;
		
		thischar = FilePtr->get();
		while(thischar!=':' && thischar!='}' && !FilePtr->eof()) { // ignore all characters until ':'
			thischar = FilePtr->get();
		}
		if(thischar!='}') {
			JSONvalue *thisvalue = new JSONvalue(FilePtr);
		}
		while(thischar!=',' && thischar!='}' && !FilePtr->eof()) { // ignore all characters until ','
			thischar = FilePtr->get();
		}
	}
}