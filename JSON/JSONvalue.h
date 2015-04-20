// JSONvalue.h

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include<iostream>
#include <iomanip>
#include<fstream>
#include "JSON.h"

using namespace std;
class JSONvalue {
	
	public:
		JSONvalue(ifstream *FilePtr);
		int istype(string typestr);
		string getString();
		double getFloat();
		vector<JSONvalue *> getArray();
		JSON *getClass();
		int getBoolean();
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
