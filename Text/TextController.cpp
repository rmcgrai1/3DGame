// TextController.cpp
// Ryan McGrail

#include <cctype>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "TextController.h"
#include "TextInterpreter.h"
#include "../Primitives/Drawable.h"
#include "../Graphics/GraphicsOGL.h"
#include "../Sound/SoundController.h"
using namespace std;

// Define Wait Timer Maximum (To Slow Down Text; Otherwise, Appears Too Quickly)
#define WAIT_TIMER_MAX 2

// Create Null Format
Format formNull = {255,255,255,1,0,0};

TextController :: TextController() : Drawable2(TYPE_MENU) {

	waitTimer = -1;

	// Create Text Interpreter Object
	teInt = new TextInterpreter();

	// Initialize to Blank Text
	setText("");
}

void TextController :: update(GraphicsOGL* gl, float deltaT) {
	
	GL = gl;

	// ADD NEXT CHAR

	// If Text is Marching...
	if(isAdvancing) {

		waitTimer -= deltaT;
		
		// Only Add if WaitTimer == -1
		if(waitTimer < -1)
			waitTimer += WAIT_TIMER_MAX;
		else
			return;

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
		else {
			SoundController :: playSound("text");
			curText += allText.at(allPos);
		}


		// If Text Ended, Pause
		if(allPos+1 >= allText.size()) {

			// Disable Text Marching, Redrawing (for Console)
			isAdvancing = false;
			//shouldRedraw = false;
		}
	}
	else {
		if(gl->getInputController()->checkLetter('u'))
			setText("");
	}

}

void TextController :: draw(GraphicsOGL* gl, float deltaT) {


	GL = gl;

	// Clear Formatting
	clearFormat();

	
	// Exit if Should Not Redraw
	if(!shouldRedraw)
		return;		

	gl->setOrtho();

	
	// PRINT TEXT

	Format f;
	char c;

	float startX, startY, dX, dY, xS, yS, e = -1;
	startX = dX = 50;
	startY = dY = 50;

	// Draw All of Text
	int si = curText.size();
	for(int i = 0; i <= curPos; i++) {

		c = curText.at(i);

		// If Character is `, Get Formatting
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
		else {
			xS = yS = 1.2*curScale;

			// Newline, Jump Down to Next Line
			if(c == '\n') { 
				dY += (8 + e)*yS;
				dX = startX;
			}
			// Space, Move Drawing X Over
			else if(c == ' ')
				dX += (8 + e)*xS;
			// Drawing Lowercase, Shrink Vertically
			else if(islower(c))
				dX += gl->drawCharScaled(dX,dY + (8*yS*.25), xS,yS*.75, c) + e*xS;
			// Drawing Uppercase, Draw Normally
			else
				dX += gl->drawCharScaled(dX,dY, xS, yS, c) + e*xS;
		}
	}

	// Draw Background Box
	
	// Outline
	gl->setColor(20,20,20);
	gl->drawRect(20,20,620,150);
	gl->setColor(180,180,180);
	gl->drawRect(20+1,20+1,620-1,150-1);

	// Fill
	gl->setColor(40,40,40,240);
	gl->fillRect(20,20,620,150);


	// Return OpenGL to Perspective Mode (3D)
	gl->setPerspective();
}

void TextController :: setText(string newText) {

	// (Re)Initialize Variables
	formatNum = 0;
	allPos = -1;
	curPos = -1;
	allText = newText.c_str();
	curText = "";
	curScale = 1;

	// Only Draw/March through Text if String Has Content
	shouldRedraw = isAdvancing = (allText.size() > 0);

	// Clear all Formats
	formatVec.clear();
}

void TextController :: setFormat(Format f) {

	int R = f.R, G = f.G, B = f.B;	
	setColor(f.R, f.G, f.B);
	int bold = f.bold;

	if(bold) {
	}
}
void TextController :: setColor(int R, int G, int B) {

	GL->setColor(R,G,B);
}


// Reset Formatting
void TextController :: clearFormat() {
	 setFormat(formNull);
}

// Erase Screen
void TextController :: clearScreen() {
	system("clear");
}

// Erase Text
void TextController :: clearTextBox() {
	curText = "";
}


bool TextController :: isTextBoxOpen() {
	return shouldRedraw;
}
