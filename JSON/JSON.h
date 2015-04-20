// JSON.h

#ifndef JSON_H
#define JSON_H

#include<iostream>
#include <iomanip>
#include<string>
#include<fstream>
#include <vector>
#include <map>
class JSONvalue;//#include "JSONvalue.h"

using namespace std;
class JSON {
	public:
		JSON(string filename);
		JSON(ifstream *FilePtr);
	private:
		void load(ifstream *FilePtr);
		
		vector<string> names;
		map<string,JSONvalue *> values;
};

#endif
