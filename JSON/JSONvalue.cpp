// JSONvalue.cpp

#include<iostream>
#include<fstream>
#include <iomanip>
#include "JSON.h"
#include "JSONvalue.h"

using namespace std;
JSONvalue::JSONvalue(ifstream *FilePtr) {
	int negate = 0;
	
	Str = "";
	Flt = 0;
	Cls = NULL;
	Boolean = 0;
	type = ""; // blank type indicates an error
	char thischar = nextnonspace(FilePtr);
	switch(thischar) {
		case '\"':
			type = "string";
			FilePtr->get(); // remove this character from buffer
			thischar = FilePtr->get();
			while(thischar!='\"' && !FilePtr->eof()) {
				if(thischar=='\\') {
					thischar = FilePtr->get();
					switch(thischar) {
						case 'b':
							Str.append(1,'\b');
							break;
						case 'f':
							Str.append(1,'\f');
							break;
						case 'n':
							Str.append(1,'\n');
							break;
						case 'r':
							Str.append(1,'\r');
							break;
						case 't':
							Str.append(1,'\t');
							break;
						case 'u':
							Str.append(1,'\\'); // temporarily just load in "\uXXXX"
							Str.append(1,'u');
							Str.append(1,FilePtr->get());
							Str.append(1,FilePtr->get());
							Str.append(1,FilePtr->get());
							Str.append(1,FilePtr->get());
							break;
						default:
							Str.append(1,thischar);
					}
				} else {
					Str.append(1,thischar);
				}
				thischar = FilePtr->get();
			}
			break;
		case '-':
			negate = 1;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			type = "float";
			thischar = FilePtr->get();
			while(isdigit(thischar) && !FilePtr->eof()) {
				Flt*=10;
				Flt+=thischar-'0';
				thischar = FilePtr->get();
			}
			if(thischar=='.') {
				double Mult = 1;
				thischar = FilePtr->get();
				while(isdigit(thischar) && !FilePtr->eof()) {
					Mult*=0.1;
					Flt+=(thischar-'0')*Mult;
					thischar = FilePtr->get();
				}
			}
			if(thischar=='e' || thischar=='E') {
				int Tot = 0;
				int negate2 = 0;
				thischar = FilePtr->get();
				if(!isdigit(thischar)) {
					switch(thischar) {
						case '-':
							negate2 = 1;
						case '+':
							
						default:
							cout << "WARNING: unrecognized character '" << thischar << "' in JSON number!!! Treating as if '+'!!\n";
					}
					thischar = FilePtr->get();
				}
				while(isdigit(thischar) && !FilePtr->eof()) {
					Tot*=10;
					Tot+=thischar-'0';
					thischar = FilePtr->get();
				}
				int i;
				for(i=0;i<Tot;i++) {
					if(negate2) {
						Flt*=0.1;
					} else {
						Flt*=10;
					}
				}
			}
			if(negate) {
				Flt*=-1;
			}
			break;
		case '{':
			type = "class";
			Cls = new JSON(FilePtr);
			break;
		case '[':
			FilePtr->get(); // remove this character from buffer
			type = "array";
			thischar = FilePtr->get();
			while(!thischar==']' && !FilePtr->eof()) {
				Array.push_back(new JSONvalue(FilePtr));
				thischar = FilePtr->get();
			}
			break;
		case 't':
			FilePtr->get(); // remove this character from buffer
			if(!FilePtr->eof() && FilePtr->get()=='r' && !FilePtr->eof() && FilePtr->get()=='u' && !FilePtr->eof() && FilePtr->get()=='e') {
				type = "boolean";
				Boolean = 1;
			} else {
				cout << "ERROR: unrecognized JSON value starting with 't'!!!\n";
			}
			break;
		case 'f':
			FilePtr->get(); // remove this character from buffer
			if(!FilePtr->eof() && FilePtr->get()=='a' && !FilePtr->eof() && FilePtr->get()=='l' && !FilePtr->eof() && FilePtr->get()=='s' && !FilePtr->eof() && FilePtr->get()=='e') {
				type = "boolean";
				Boolean = 0;
			} else {
				cout << "ERROR: unrecognized JSON value starting with 'f'!!!\n";
			}
			break;
		case 'n':
			FilePtr->get(); // remove this character from buffer
			if(!FilePtr->eof() && FilePtr->get()=='u' && !FilePtr->eof() && FilePtr->get()=='l' && !FilePtr->eof() && FilePtr->get()=='l') {
				type = "null";
			} else {
				cout << "ERROR: unrecognized JSON value starting with 'n'!!!\n";
			}
			break;
		default:
			cout << "ERROR: unrecognized JSON value starting with '" << thischar << "'!!!\n";
	}
}

JSONvalue::~JSONvalue() {
	if(Cls) {
		delete Cls;
	}
	while(Array.size()) {
		delete Array.back();
		Array.pop_back();
	}
}

int JSONvalue::istype(string typestr) {
	return typestr==type;
}

string JSONvalue::getType() {
	return type;
}

string JSONvalue::getString() {
	return Str;
}

double JSONvalue::getFloat() {
	return Flt;
}

vector<JSONvalue *> JSONvalue::getArray() {
	return Array;
}

JSON *JSONvalue::getClass() {
	return Cls;
}

int JSONvalue::getBoolean() {
	return Boolean;
}

vector<string> JSONvalue::getStringArray() {
	vector<string> reverse;
	vector<JSONvalue *>::iterator i;
	for(i=Array.begin();i!=Array.end();i++) {
		if((*i)->istype("string")) {
			reverse.push_back((*i)->getString());
		}
	}
	vector<string> output;
	while(reverse.size()) { // reverse order of list because of reversing in earlier copying
		output.push_back(reverse.back());
		reverse.pop_back();
	}
	return output;
}

vector<double> JSONvalue::getFloatArray() {
	vector<double> reverse;
	vector<JSONvalue *>::iterator i;
	for(i=Array.begin();i!=Array.end();i++) {
		if((*i)->istype("float")) {
			reverse.push_back((*i)->getFloat());
		}
	}
	vector<double> output;
	while(reverse.size()) { // reverse order of list because of reversing in earlier copying
		output.push_back(reverse.back());
		reverse.pop_back();
	}
	return output;
}

vector<JSON *> JSONvalue::getClassArray() {
	vector<JSON *> reverse;
	vector<JSONvalue *>::iterator i;
	for(i=Array.begin();i!=Array.end();i++) {
		if((*i)->istype("class")) {
			reverse.push_back((*i)->getClass());
		}
	}
	vector<JSON *> output;
	while(reverse.size()) { // reverse order of list because of reversing in earlier copying
		output.push_back(reverse.back());
		reverse.pop_back();
	}
	return output;
}

vector<int> JSONvalue::getBooleanArray() {
	vector<int> reverse;
	vector<JSONvalue *>::iterator i;
	for(i=Array.begin();i!=Array.end();i++) {
		if((*i)->istype("boolean")) {
			reverse.push_back((*i)->getBoolean());
		}
	}
	vector<int> output;
	while(reverse.size()) { // reverse order of list because of reversing in earlier copying
		output.push_back(reverse.back());
		reverse.pop_back();
	}
	return output;
}

vector<vector<JSONvalue *> > JSONvalue::getArrayArray() {
	vector<vector<JSONvalue *> > reverse;
	vector<JSONvalue *>::iterator i;
	for(i=Array.begin();i!=Array.end();i++) {
		if((*i)->istype("array")) {
			reverse.push_back((*i)->getArray());
		}
	}
	vector<vector<JSONvalue *> > output;
	while(reverse.size()) { // reverse order of list because of reversing in earlier copying
		output.push_back(reverse.back());
		reverse.pop_back();
	}
	return output;
}

char JSONvalue::nextnonspace(ifstream *FilePtr) {
	char thischar = FilePtr->peek();
	while(isspace(thischar) && !FilePtr->eof()) {
		thischar = FilePtr->get();
		thischar = FilePtr->peek();
	}
	return thischar;
}