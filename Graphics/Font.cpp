// Font.cpp


#include <stdio.h>
#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "Texture.h"
#include "Font.h"
//#include "../Global.h"
using namespace std;


Font2D :: Font2D(string fontName, bool ca) {
	isCaseEnabled = ca;

	fontDir = "Resources/Fonts/" + fontName + "/";
	char c;


	//string cwd;
	//cwd = getPackageManager().getPackageInfo("com.example.app", 0).applicationInfo.dataDir;
	//	__android_log_print(ANDROID_LOG_INFO, "Junk", "%s", cwd.c_str());


	for(int i = 0; i < 26; i++) {
		addChar('a' + i);
		addChar('A' + i);
	}

	for(int i = 0; i < 10; i++)
		addChar('0' + i);

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

int Font2D :: getWidth() {
	return getChar('A')->getWidth();
}

int Font2D :: getHeight() {
	return getChar('A')->getHeight();
}

Texture* Font2D :: getChar(char c) {
	if(isalpha(c)) {
		return fontMap[c];
	}
	else// if(isdigit(c))
		return fontMap[c];

	//return NULL;
}

void Font2D :: addChar(char c) {
	int ascii = (int) (c);
	char cc[4];

	sprintf(cc, "%i", ascii);

	addChar(c, (fontDir + cc) + ".png");
}

void Font2D :: addChar(char c, string fileName) {
	string str = "Loading file for ";
	str = str + c + " at " + fileName;

	string name = "";
		name += c;

	Texture* t = new Texture(name, fileName, true);

	fontMap[c] = t;
}
