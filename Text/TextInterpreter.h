// TextInterpreter.h

#ifndef TEXTINTERPRETER_H
#define TEXTINTERPRETER_H

#include "TextController.h"
#include <string>
using namespace std;

class TextInterpreter {
	public:					// PUBLIC
		TextInterpreter();			// Constructor
		Format generateFormat(string);		// Generate Format

	private:				// PRIVATE
		char eatOne(string&);			// Remove One Char
		int checkStr(string&, string);		// Remove Substring
		int checkStrCase(string&, string);	// Remove SS (Any Case)
		int checkStrSpace(string&, string);	// Remove SS (& Spaces)
		int checkWhiteSpace(string&);		// Remove White Space
		char readChar(string&);			// Read One Char
		int readHex(string&);			// Read Hex Digit
		int readHex2(string&);			// Read 2 Hex Digits
		float readDec(string&);			// Read Decimal
};

#endif
