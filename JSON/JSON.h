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
	friend ostream& operator<<(ostream&, JSON);
	public:
		JSON(string filename);
		JSON(ifstream *FilePtr);
		~JSON();
		string getDataType(string key);
		string getString(string key);
		double getFloat(string key);
		JSON *getClass(string key);
		int getBoolean(string key);
		vector<JSONvalue *> getArray(string key);
		vector<string> getStringArray(string key);
		vector<double> getFloatArray(string key);
		vector<JSON *> getClassArray(string key);
		vector<int> getBooleanArray(string key);
		vector<vector<JSONvalue *> > getArrayArray(string key);
	private:
		void load(ifstream *FilePtr);
		
		vector<string> names;
		map<string,JSONvalue *> values;
};

#endif
