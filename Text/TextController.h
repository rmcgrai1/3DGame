// TextController.h


#ifndef TEXTCONTROLLER_H
#define TEXTCONTROLLER_H


	// Initialize Format Struct
	typedef struct Format {
		int R;			// Color
		int G;
		int B;
		float size;		// Size
		int bold;		// Bold
		int underline;		// Underline
	} Format;

#include <vector>
#include <string>
#include "../Graphics/GraphicsOGL.h"
#include "TextInterpreter.h"
#include "../Primitives/Drawable.h"
using namespace std;

class TextInterpreter;
class TextController : public Drawable2 {

	public:					// PUBLIC
		TextController();			// Contructor
		void update(GraphicsOGL*, float);	//
		void draw(GraphicsOGL*, float);		// Drawing Text
		void setText(string);			// Setting Text
		void clearScreen();			// Clearing Screen
		void clearTextBox();			// Clearing Text Box
		void clearFormat();			// Resetting Format
		void setFormat(Format);			// Setting Format
		void setColor(int,int,int);		// Setting Color
		bool isTextBoxOpen();


	private:				// PRIVATE
	
		bool shouldRedraw;			// Should Keep Drawing?
		int formatNum;				// Number of Formats
		bool isAdvancing;			// Is Text Marching?
		int allPos;				// "Real" Position
		int curPos;				// "Display" Position

		float waitTimer;
		TextInterpreter* teInt;			// Text Interpreter
		string allText;				// "Real" Text
		string curText;				// "Display" Text
		vector<Format> formatVec;		// Format Vector
		float curScale;

		GraphicsOGL* GL;
};

#endif
