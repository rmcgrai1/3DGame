// InputController.h
// Ryan McGrail

#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <map>
using namespace std;

class InputController {

	public:
		InputController();									// Constructor
		void updateMouse(int,int,int,int);					// Callback for Updating Mouse Clicks (Used by GLUT)
		void updatePassiveMouse(int,int);					// Callback for Updating Mouse Motion (Used by GLUT)
		void updateKeyboard(unsigned char, int, int);		// Callback for Updating Key Presses (Used by GLUT)
		void updateKeyboardUp(unsigned char, int, int);		// Callback for Updating Key Releases (Used by GLUT)
		void updateKeyboardSpecial(int, int, int);			// Callback for Updating Special Key Presses (Used by GLUT)
		void updateKeyboardSpecialUp(int, int, int);		// Callback for Updating Special Key Releases (Used by GLUT)

		bool checkLeftMouse();								// Get State of Left Mouse
		bool checkRightMouse();								// Get State of Right Mouse

		bool checkKey(unsigned char);						// Check Key State
		bool checkLetter(char);								// Check Letter State
		void setLetter(char, bool);							// Set Letter State
		bool getShift();									// Check Shift State
		float getWASDDir();									// Get Current Held WASD Direction
		bool checkWASD(char);								// Check WASD State
		void setWASD(char, bool);							// Set WASD State

		int getMouseX();									// Get Mouse X
		int getMouseY();									// Get Mouse Y

	private:
		static InputController* mainInp;					// Main InputController Object

		bool* wasdArray;									// WASD Key Array
		bool* keyArray;										// ASCII Key Array
		bool* letterArray;									// Letter Key Array
		bool* mouseArray;									// Mouse State Array

		int mouseX;											// Mouse X
		int mouseY;											// Mouse Y

		bool isShiftDown;									// Shift Key Status
};

#endif
