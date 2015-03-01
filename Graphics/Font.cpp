// Font.cpp


#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "Texture.h"
#include "Font.h"
using namespace std;


Font2D :: Font2D(string fontName, bool ca, int argc, char** argv) {
	isCaseEnabled = ca;

	fontDir = "Resources/Fonts/" + fontName + "/";
	char c;

	if(!isCaseEnabled) {
		for(int i = 0; i < 26; i++)
			addChar('a' + i,argc,argv);
		for(int i = 0; i < 10; i++)
			addChar('0' + i,argc,argv);

		addChar(',',argc,argv);
		addChar('!',argc,argv);
		addChar('.',argc,argv);
		addChar(';',argc,argv);
		addChar(':',argc,argv);
		addChar('-',argc,argv);
	}
}

Texture* Font2D :: getChar(char c) {
	if(isalpha(c)) {
		if(!isCaseEnabled)
			return fontMap[tolower(c)];
		else
			return fontMap[c];
	}
	else// if(isdigit(c))
		return fontMap[c];

	//return NULL;
}

void Font2D :: addChar(char c, int argc, char** argv) {
	addChar(c, (fontDir + c) + ".png", argc, argv);
}

void Font2D :: addChar(char c, string fileName, int argc, char** argv) {
	Texture* t = new Texture(fileName, true, argc, argv);

	fontMap[c] = t;
}
