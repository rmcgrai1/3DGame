// FontController.h
// Ryan McGrail

#ifndef FONTCONTROLLER_H
#define FONTCONTROLLER_H

#include <map>
#include <string>
#include "Font.h"
using namespace std;

class FontController {
	public:
		FontController();								// Constructor
		Font2D* getFont(string);						// Getting Font w/ Name
		
	private:
		void initialize();								// Initialize all Fonts
		void addFont(string,bool);						// Load Font

		map<string, Font2D*> fontMap;					// Map of Fonts
};

#endif
