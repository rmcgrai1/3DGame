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

JSON::~JSON() {
	while(names.size()) {
		delete values[names.back()];
		names.pop_back();
	}
}

string JSON::getDataType(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getType();
	}
	return ""; // blank type indicates an error
}

string JSON::getString(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getString();
	}
	return "";
}

double JSON::getFloat(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getFloat();
	}
	return 0;
}

JSON *JSON::getClass(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getClass();
	}
	return NULL;
}

int JSON::getBoolean(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getBoolean();
	}
	return 0;
}

vector<JSONvalue *> JSON::getArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getArray();
	}
	vector<JSONvalue *> output;
	return output;
}

vector<string> JSON::getStringArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getStringArray();
	}
	vector<string> output;
	return output;
}

vector<double> JSON::getFloatArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getFloatArray();
	}
	vector<double> output;
	return output;
}

vector<JSON *> JSON::getClassArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getClassArray();
	}
	vector<JSON *> output;
	return output;
}

vector<int> JSON::getBooleanArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getBooleanArray();
	}
	vector<int> output;
	return output;
}

vector<vector<JSONvalue *> > JSON::getArrayArray(string key) {
	JSONvalue *ThisValue = values[key];
	if(ThisValue) {
		return ThisValue->getArrayArray();
	}
	vector<vector<JSONvalue *> > output;
	return output;
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
			names.push_back(thisnameVal->getString());
			values[thisnameVal->getString()] = thisvalue;
		}
		while(thischar!=',' && thischar!='}' && !FilePtr->eof()) { // ignore all characters until ','
			thischar = FilePtr->get();
		}
	}
}


ostream& operator<<(ostream& output, JSON json) {
	output << "{";
	vector<string>::iterator i;
	for(i=json.names.begin();i!=json.names.end();i++) {
		output << (*i) << ":" << *(json.values[(*i)]) << "|\n";
	}
	output << "}";
	return output;
}