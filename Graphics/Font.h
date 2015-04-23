// Font.h
// Ryan McGrail

#ifndef FONT_H
#define FONT_H

#include <string>
#include <map>
#include "Texture.h"
using namespace std;

class Font2D {
	public:
		Font2D(string,bool);			// Constructor
		Texture* getChar(char);			// Get Character Texture
		int getWidth();					// Get Width of Font Characters
		int getHeight();				// Get Height of Font Characters

	private:
		void addChar(char,string);		// Add Character to Font (Given Filename)
		void addChar(char);				// Add Character to Font (Assuming Filename)

		map<char, Texture*> fontMap;	// Font Character -> Texture Map
		bool isCaseEnabled;				// Are Letters Available for UPPERCASE and lowercase?
		string fontDir;					// Font Directory
};

#endif
