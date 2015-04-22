// JSONvalue.h

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include<iostream>
#include <iomanip>
#include<fstream>
#include "JSON.h"

using namespace std;
class JSONvalue {
	friend ostream& operator<<(ostream&, JSONvalue);
	public:
		JSONvalue(ifstream *FilePtr);
		~JSONvalue();
		int istype(string typestr);
		string getType();
		string getString();
		double getFloat();
		vector<JSONvalue *> getArray();
		JSON *getClass();
		int getBoolean();
		vector<string> getStringArray();
		vector<double> getFloatArray();
		vector<JSON *> getClassArray();
		vector<int> getBooleanArray();
		vector<vector<JSONvalue *> > getArrayArray();
	private:
		char nextnonspace(ifstream *FilePtr);
		
		string type;
		string Str;
		double Flt;
		vector<JSONvalue *> Array;
		JSON *Cls;
		int Boolean;
};

#endif
