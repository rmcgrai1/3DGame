// InputController.cpp
// Ryan McGrail

#include <iostream>
#include "InputController.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../Functions/Math2D.h"
using namespace std;

// GLUT Callbacks
InputController* inp;
void mouseCallback(int button, int state, int x, int y) {
	inp->updateMouse(button, state, x, y);
}
void passiveMouseCallback(int x, int y) {
	inp->updatePassiveMouse(x, y);
}
void keyboardCallback(unsigned char key, int x, int y) {
	inp->updateKeyboard(key, x, y);
}
void keyboardUpCallback(unsigned char key, int x, int y) {
	inp->updateKeyboardUp(key, x, y);
}
void keyboardSpecialCallback(int key, int x, int y) {
	inp->updateKeyboardSpecial(key, x, y);
}
void keyboardSpecialUpCallback(int key, int x, int y) {
	inp->updateKeyboardSpecialUp(key, x, y);
}


// Constructor
InputController :: InputController() {
	inp = this;

	// Initialize WASD Array
	wasdArray = new bool[4];
	wasdArray[0] = false;
	wasdArray[1] = false;
	wasdArray[2] = false;
	wasdArray[3] = false;

	// Initialize Letter Array
	letterArray = new bool[26];
	for(int i = 0; i < 26; i++)
		letterArray[i] = false;

	// Initialize ASCII Key Array
	keyArray = new bool[255];
	for(int i = 0; i < 255; i++)
		keyArray[i] = false;

	// Initialize Mouse Array
	mouseArray = new bool[3];
	for(int i = 0; i < 3; i++)
		mouseArray[i] = false;

	isShiftDown = false;

	// Disable Keypresses Repeating When Held
	glutSetKeyRepeat(0);

	// Initialize GLUT Connections to Callbacks
	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(passiveMouseCallback);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(keyboardSpecialCallback);
	glutSpecialUpFunc(keyboardSpecialUpCallback);
}

// Get Mouse X
int InputController :: getMouseX() {
	return mouseX;
}

// Get Mouse Y
int InputController :: getMouseY() {
	return mouseY;
}

// Set State of Mouse Buttons
void InputController :: updateMouse(int button, int state, int x, int y) {

	bool isPressed = (state == GLUT_DOWN);

	// Set State of Current Mouse Button
	switch(button) {
		case GLUT_LEFT_BUTTON:		mouseArray[0] = isPressed;
						break;
		case GLUT_RIGHT_BUTTON:		mouseArray[1] = isPressed;
						break;
		case GLUT_MIDDLE_BUTTON:	mouseArray[2] = isPressed;
						break;
	}
}

// Set State of Mouse Position
void InputController :: updatePassiveMouse(int x, int y) {
	mouseX = x;
	mouseY = y;
}

// Set State of Key Presses
void InputController :: updateKeyboard(unsigned char key, int x, int y) {
	char lKey = tolower(key);

	isShiftDown = (glutGetModifiers() == GLUT_ACTIVE_SHIFT);

	setLetter(key, true);
	switch(lKey) {
		case 'w':
		case 'a':
		case 's':
		case 'd':	setWASD(lKey, true);
			break;
	}

	keyArray[key] = true;
}

// Set State of Key Releases
void InputController :: updateKeyboardUp(unsigned char key, int x, int y) {
	char lKey = tolower(key);

	setLetter(key, false);
	switch(lKey) {
		case 'w':
		case 'a':
		case 's':
		case 'd':	setWASD(lKey, false);
			break;
	}

	keyArray[key] = false;
}
void InputController :: updateKeyboardSpecial(int key, int x, int y) {
	isShiftDown = true;
}
void InputController :: updateKeyboardSpecialUp(int key, int x, int y) {
	isShiftDown = false;
}


// Check Left Mouse Button State
bool InputController :: checkLeftMouse() {
	return mouseArray[0];
}

// Check Right Mouse Button State
bool InputController :: checkRightMouse() {
	return mouseArray[1];
}

// Check ASCII Key State
bool InputController :: checkKey(unsigned char key) {
	return keyArray[key];
}

// Check Letter State
bool InputController :: checkLetter(char key) {

	// If Non-Letter, Return False!
	if(!isalpha(key))
		return false;
	// Otherwise, Return State
	else
		return letterArray[tolower(key)-'a'];
}

// Set Letter State
void InputController :: setLetter(char key, bool down) {

	// If Nonletter, Ignore
	if(!isalpha(key))
		return;
	// Otherwise, Set State
	else
		letterArray[tolower(key)-'a'] = down;
}

// Check Shift State
bool InputController :: getShift() {
	return isShiftDown;
}

// Get Current Held WASD Direction
float InputController :: getWASDDir() {
	int hDir, vDir;

	// Get Horizontal Combination of A & D Keys
	if(checkWASD('a') && !checkWASD('d'))
		hDir = -1;
	else if(!checkWASD('a') && checkWASD('d'))
		hDir = 1;
	else
		hDir = 0;

	// Get Vertical Combination of W & S Keys
	if(checkWASD('w') && !checkWASD('s'))
		vDir = 1;
	else if(!checkWASD('w') && checkWASD('s'))
		vDir = -1;
	else
		vDir = 0;

	// If No Keys are Held, or Only <> and/or ^v, Return -1
	if(hDir == 0 && vDir == 0)
		return -1;
	//Otherwise, Return the Direction Given by the Points
	else
		return calcPtDir(0,0,hDir,vDir);
}

// Check WASD State
bool InputController :: checkWASD(char key) {

	// Return WASD State
	switch(key) {
		case 'w':	return wasdArray[0];
			break;
		case 'a':	return wasdArray[1];
			break;
		case 's':	return wasdArray[2];
			break;
		case 'd':	return wasdArray[3];
			break;
	}

	// Return False Otherwise
	return false;
}

// Set WASD State
void InputController :: setWASD(char key, bool down) {

	// Set WASD
	switch(key) {
		case 'w':	wasdArray[0] = down;
			break;
		case 'a':	wasdArray[1] = down;
			break;
		case 's':	wasdArray[2] = down;
			break;
		case 'd':	wasdArray[3] = down;
			break;
	}
}