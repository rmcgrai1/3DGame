// FileIO.h
// Ryan McGrail

#ifndef FILEIO_H
#define FILEIO_H

#include <string>
using namespace std;

class FileIO {

	public:
		static bool readFileIntoString(string, string&);	// Load File into String

	private:
		FileIO();											// Constructor
};

#endif

