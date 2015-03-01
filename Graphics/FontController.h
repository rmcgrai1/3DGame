// FontController.h

#ifndef FONTCONTROLLER_H
#define FONTCONTROLLER_H

#include <map>
#include <string>
#include "Font.h"
using namespace std;

class FontController {
	public:
		FontController(int,char**);
		Font2D* getFont(string);
		
	private:
		void initialize(int,char**);
		void addFont(string,bool,int,char**);

		map<string, Font2D*> fontMap;
};

#endif
