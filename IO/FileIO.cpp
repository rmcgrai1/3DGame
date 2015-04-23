// FileIO.cpp
// Ryan McGrail

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string>
#include "FileIO.h"
using namespace std;

// Loading File into String
bool FileIO :: readFileIntoString(string pFileName, string& str) {
	// Load File
    ifstream f(pFileName.c_str());
    
    bool ret = false;
    
    if (f.is_open()) {
	
		// Read All Lines into String
        string line;
        while (getline(f, line)) {
            str.append(line);
            str.append("\n");
        }
        
		// Close File
        f.close();
        
        ret = true;
    }
    
    return ret;
}
