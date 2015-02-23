// FileIO.cpp


#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string>
#include "FileIO.h"
using namespace std;

bool FileIO :: readFileIntoString(string pFileName, string& outFile)
{
    ifstream f(pFileName.c_str());
    
    bool ret = false;
    
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    
    return ret;
}
