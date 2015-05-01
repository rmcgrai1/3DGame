// FontController.cpp
// Ryan McGrail

#include <map>
#include <string>
#include "Font.h"
#include "FontController.h"
using namespace std;

// Constructor
FontController :: FontController() {

	// Load all Fonts
	initialize();
}

// Getting Font w/ Name
Font2D* FontController :: getFont(string name) {
	return fontMap[name];
}		

// Initializing all Fonts
void FontController :: initialize() {
	addFont("8bit",true);
}

// Adding new Font
void FontController :: addFont(string name, bool hasCaps) {
	fontMap[name] = new Font2D(name, hasCaps);
}
