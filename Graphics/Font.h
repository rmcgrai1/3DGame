// Font.h

#ifndef FONT_H
#define FONT_H

#include <string>
#include <map>
#include "Texture.h"
using namespace std;

class Font {
	public:
		Font(string,bool);
		Texture* getChar(char);

	private:
		void addChar(char,string);
		void addChar(char);

		map<char, Texture*> fontMap;
		bool isCaseEnabled;
		string fontDir;
};

#endif
