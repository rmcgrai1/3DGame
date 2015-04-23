// TextInterpreter.cpp
// Ryan McGrail

#include <cstdlib>
#include <iostream>
#include "TextInterpreter.h"
#include "TextController.h"
#include <string>
using namespace std;

// Constructor
TextInterpreter :: TextInterpreter() {
}

char TextInterpreter :: eatOne(string& input) {

	// Get Char from String
	char c = input[0];
	
	// Erase Char from String
	input.erase(input.begin(),input.begin()+1);	

	// Return Char
	return c;
}

int TextInterpreter :: checkStr(string& str, string substr) {
	int len, subLen;

	// Get Lengths of String and Substring
	len = str.size();
	subLen = substr.size();

	// Return False if Substring Longer than String	
	if(len < subLen)
		return false;

	// If Any of Chars in Substring and String don't Match, Return False
	for(int i = 0; i < subLen; i++)
		if(str[i] != substr[i])
			return false;

	// Erase Word
	str.erase(str.begin(),str.begin()+subLen);

	// Return Successful!
	return true;
}

int TextInterpreter :: checkStrCase(string& str, string substr) {
	int len, subLen;

	// Get Lengths of String and Substring
	len = str.size();
	subLen = substr.size();

	// Return False if Substring Longer than String
	if(len < subLen)
		return false;

	// If Any of Chars in Substring and String don't Match, Return False
	for(int i = 0; i < subLen; i++)
		if(toupper(str[i]) != toupper(substr[i]))
			return false;

	// Erase Word
	str.erase(str.begin(),str.begin()+subLen);

	// Return Successful!
	return true;
}

int TextInterpreter :: checkWhiteSpace(string& str) {

	int success = false;

	// Erase as Many Whitespace Characters as Possible
	while(checkStr(str," "));

	return success;
}

int TextInterpreter :: checkStrSpace(string& str, string substr) {

	int success;

	// Remove Pre- and Post- Whitespace, Check for String Between
	checkWhiteSpace(str);
	success = checkStr(str,substr);
	checkWhiteSpace(str);

	return success;
}

char TextInterpreter :: readChar(string& input) {
	
	// If Cannot Read Char, Return Space
	if(input.size() == 0)
		return ' ';

	// Otherwise, Return First Char
	else
		return eatOne(input);
}

int TextInterpreter :: readHex(string& input) {

	char c = toupper(input[0]);

	// Check for Digits 0-9
	if(isdigit(c)) {
		for(int i = 0; i <= 9; i++)

			// If Char is this Digit...
			if(c == '0'+i) {

				// Remove Char from String, Return
				eatOne(input);
				return i;
			}
	}
	// Check for Digits A-F
	else if(isalpha(c))
		for(int i = 0; i < 6; i++)
	
			// If Char is this Digit
			if(c == 'A'+i) {
			
				// Remove Char from String, Return
				eatOne(input);
				return 10+i;
			}

	// Return -1 if Failed
	return -1;
}

int TextInterpreter :: readHex2(string& input) {
	int dig1, dig2;

	// Read 2 Hexidecimal Digits
	dig1 = readHex(input);
	dig2 = readHex(input);

	// Return Base 10 #
	return dig1*16 + dig2;
}

float TextInterpreter :: readDec(string& input) {
	string numStr = "";
	float num;
	
	// While Not Reached End of #...
	while(!(checkStr(input, " ") || checkStr(input, ";"))) {

		// Add Digit to String
		numStr += eatOne(input);
	}

	// Convert String into Float
	num = atof(numStr.c_str());

	return num;
}

Format TextInterpreter :: generateFormat(string input) {
	// Create Null Format
	Format fR = {255,255,255,1,0,0};

	// Remove First `
	checkStr(input, "`");

	int acted = false;

	// Run Until No More Commands Left
	do {
		acted = false;


		// Claim Starting White Space (Just in Case)
		checkWhiteSpace(input);

		// COLOR FORMATTING
		if(checkStrCase(input, "color") || checkStrCase(input, "c")) {
			// Remove = or : if Present
			checkWhiteSpace(input);
				checkStr(input, "=");
				checkStr(input, ":");
			checkWhiteSpace(input);

			// Remove #
			checkStr(input, "#");

			// Set Colors in Format
			fR.R = readHex2(input);
			fR.G = readHex2(input);
			fR.B = readHex2(input);			

			acted = true;
		}
		// SIZE FORMATTING
		else if(checkStrCase(input, "size") || checkStrCase(input, "s")) {
			// Remove = or : if Present
			checkWhiteSpace(input);
				checkStr(input, "=");
				checkStr(input, ":");
			checkWhiteSpace(input);

			// Set Format Size
			fR.size = readDec(input);

			acted = true;
		}
		// BOLD FORMATTING
		else if(checkStrCase(input, "bold") || checkStrCase(input, "b")) {
			fR.bold = true;
			acted = true;
		}
		// UNDERLINE FORMATTING
		else if(checkStrCase(input, "underline") || checkStrCase(input, "u")) {
			fR.underline = true;
			acted = true;
		}

		// Get Semicolon Between Commands
		checkStrSpace(input, ";");

	} while(acted);


	// Return Format
	return fR;
}
