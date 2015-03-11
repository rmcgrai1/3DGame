// InputController.cpp

#include <iostream>
#include "InputController.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "../Functions/Math2D.h"
using namespace std;

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


InputController :: InputController() {
	inp = this;

	wasdArray = new bool[4];
	wasdArray[0] = false;
	wasdArray[1] = false;
	wasdArray[2] = false;
	wasdArray[3] = false;

	letterArray = new bool[26];
	for(int i = 0; i < 26; i++)
		letterArray[i] = false;

	mouseArray = new bool[3];
	for(int i = 0; i < 3; i++)
		mouseArray[i] = false;


	isShiftDown = false;

	glutSetKeyRepeat(0);

	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(passiveMouseCallback);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(keyboardSpecialCallback);
}

int InputController :: getMouseX() {
	return mouseX;
}

int InputController :: getMouseY() {
	return mouseY;
}

		
void InputController :: updateMouse(int button, int state, int x, int y) {
	//GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON.  GLUT_UP or GLUT_DOWN

	bool isPressed = (state == GLUT_DOWN);

	switch(button) {
		case GLUT_LEFT_BUTTON:		mouseArray[0] = isPressed;
						break;
		case GLUT_RIGHT_BUTTON:		mouseArray[1] = isPressed;
						break;
		case GLUT_MIDDLE_BUTTON:	mouseArray[2] = isPressed;
						break;
	}
}
void InputController :: updatePassiveMouse(int x, int y) {
	mouseX = x;
	mouseY = y;
}
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
}
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
}
void InputController :: updateKeyboardSpecial(int key, int x, int y) {
	isShiftDown = (glutGetModifiers() == GLUT_ACTIVE_SHIFT);
}

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

bool InputController :: getShift() {
	return isShiftDown;
}

bool InputController :: checkLeftMouse() {

	return mouseArray[0];
}

bool InputController :: checkRightMouse() {

	return mouseArray[1];
}

bool InputController :: checkWASD(char key) {
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

	return false;
}

void InputController :: setWASD(char key, bool down) {
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

bool InputController :: checkLetter(char key) {

	if(!isalpha(key))
		return false;
	else
		return letterArray[tolower(key)-'a'];
}

void InputController :: setLetter(char key, bool down) {
	if(!isalpha(key))
		return;
	else
		letterArray[tolower(key)-'a'] = down;
}


