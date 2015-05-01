// Font.cpp
// Ryan McGrail

#include <stdio.h>
#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "Texture.h"
#include "Font.h"
using namespace std;


// Constructor
Font2D :: Font2D(string fontName, bool ca) {
	isCaseEnabled = ca;

	// Get Path to Font Directory
	fontDir = "Resources/Fonts/" + fontName + "/";
	char c;

	// Add Alphabetical Characters
	for(int i = 0; i < 26; i++) {
		addChar('a' + i);
		addChar('A' + i);
	}

	// Add Numbers
	for(int i = 0; i < 10; i++)
		addChar('0' + i);

	// Add Punctuation
	addChar(',');
	addChar('!');
	addChar('?');
	addChar('.');
	addChar(';');
	addChar(':');
	addChar('+');
	addChar('-');
	addChar('(');
	addChar(')');
	addChar('[');
	addChar(']');
	addChar('\\');
	addChar('/');
}

// Getting Width of Font (Assumed Constant)
int Font2D :: getWidth() {
	return getChar('A')->getWidth();
}

// Getting Height of Font (Assumed Constant)
int Font2D :: getHeight() {
	return getChar('A')->getHeight();
}

// Getting Char Texture
Texture* Font2D :: getChar(char c) {
	return fontMap[c];
}

// Adding New Char Texture
void Font2D :: addChar(char c) {
	int ascii = (int) (c);
	char cc[4];

	// Get Number as Ascii
	sprintf(cc, "%i", ascii);

	// Add Char
	addChar(c, (fontDir + cc) + ".png");
}

// Adding New Char Texture, Specifiying Name
void Font2D :: addChar(char c, string fileName) {

	// Get Name of Texture (Letter)
	string name = "";
		name += c;

	// Create Texture, Add to Map
	fontMap[c] = new Texture(name, fileName, true);
}
