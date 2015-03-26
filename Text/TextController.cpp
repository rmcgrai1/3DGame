// TextController.cpp


#include <cctype>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "TextController.h"
#include "TextInterpreter.h"
using namespace std;

// Create Null Format
Format formNull = {255,255,255,1,0,0};

TextController :: TextController() {

	// Create Text Interpreter Object
	teInt = new TextInterpreter();

	// Initialize to Blank Text
	setText("");
}

void TextController :: draw() {

	// Clear Formatting
	clearFormat();
	
	// Print Nothing to Ensure Formatting is Set When Window Closes
	cout << "" << flush;

	// Exit if Should Not Redraw
	if(!shouldRedraw)
		return;	


	// Clear Screen
	clearScreen();
	

	// ADD NEXT CHAR

	// If Text is Marching...
	if(isAdvancing) {

		// Increment Text Positions
		allPos++;
		curPos++;

		if(allText.at(allPos) == '`') {

			// If ``, Add `f-1` to Text
			if(allText.at(allPos+1) == '`') {
				allPos++;
				curText += "`f-1`";
				curPos += 4;
			}
			// Otherwise, Create New Format!
			else { 
				string formatText = "`";
				char c;

				// Get Format Text
				do {
					allPos++;
					c = allText.at(allPos);

					formatText += c;
				} while(c != '`');

				// Create Format with Text Interpreter
				formatVec.push_back(teInt->generateFormat(formatText));

				// Add Format ID to String
				string fTxt = "`f" + to_string(static_cast<long long>(formatNum++)) + "`";
				curText += fTxt;

				// Increment Position
				curPos += fTxt.size()-1;
			}
		}		
		// Otherwise, Add Char to Text
		else
			curText += allText.at(allPos);


		// If Text Ended, Pause
		if(allPos+1 >= allText.size()) {

			// Disable Text Marching, Redrawing (for Console)
			isAdvancing = false;
			shouldRedraw = false;
		}
	}

	
	// PRINT TEXT

	Format f;
	char c;

	// Draw All of Text
	int si = curText.size();
	for(int i = 0; i <= curPos; i++) {

		c = curText.at(i);

		if(c == '`') {

			i += 2;

			int ind = -2;

			string indText = "";
			while((c = curText.at(i)) != '`') {

				// If Found - Sign, MUST be Null Format
				if(c == '-')
					ind = -1;

				// Otherwise, Add Text to String
				if(ind == -2)
					indText += to_string(static_cast<long long>(c - '0'));

				// Increment Position
				i++;
			}

			// If Index is Still -2, Convert Text to Int
			if(ind == -2)
				ind = atoi(indText.c_str());

			// Get Format from Index
			if(ind == -1)
				f = formNull;
			else
				f = formatVec.at(ind);

			// Enable Format
			setFormat(f);
		}
		// Otherwise, Print Character
		else
			cout << c << flush;
	}
}

void TextController :: setText(string newText) {

	// (Re)Initialize Variables
	formatNum = 0;
	allPos = -1;
	curPos = -1;
	allText = newText.c_str();
	curText = "";

	// Only Draw/March through Text if String Has Content
	shouldRedraw = isAdvancing = (allText.size() > 0);

	// Clear all Formats
	formatVec.clear();
}

void TextController :: setFormat(Format f) {

	int R = f.R, G = f.G, B = f.B;	
	//setColor(f.R, f.G, f.B);
	int bold = f.bold;

	string ul = "";
	if(f.underline)
		ul += ";4";

	if(bold) {
		if(R > G && R > B)
			cout << "\033[1" + ul + ";31m";
		else if(G > R && G > B)
			cout << "\033[1" + ul + ";32m";
		else if(B > G && B > R)
			cout << "\033[1" + ul + ";34m";
		else
			cout << "\033[1" + ul + "m";
	} 
	else {
		if(R > G && R > B)
			cout << "\033[31" + ul + "m";
		else if(G > R && G > B)
			cout << "\033[32" + ul + "m";
		else if(B > G && B > R)
			cout << "\033[34" + ul + "m";
		else {
			if(ul != "")
				ul = "4";
			else
				ul = "0";
			cout << "\033[" + ul + "m";
		}
	}
}
void TextController :: setColor(int R, int G, int B) {

	//gl->setColor(R/255.,G/255.,B/255.,1);

	if(R > G && R > B)
		cout << "\033[31m";
	else if(G > R && G > B)
		cout << "\033[32m";
	else if(B > G && B > R)
		cout << "\033[34m";
	else
		cout << "\033[0m";
}


// Reset Formatting
void TextController :: clearFormat() {
	 cout << "\033[0m";
}

// Erase Screen
void TextController :: clearScreen() {
	system("clear");
}

// Erase Text
void TextController :: clearTextBox() {
	curText = "";
}
