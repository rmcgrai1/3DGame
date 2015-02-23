// FontController.h

#ifndef FONTCONTROLLER_H
#define FONTCONTROLLER_H

#include <map>
#include <string>
#include "Font.h"
using namespace std;

class FontController {
	public:
		FontController();
		Font* getFont(string);
		
	private:
		void initialize();
		void addFont(string,bool);

		map<string, Font*> fontMap;
};

#endif
