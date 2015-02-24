// InputController.cpp

#include "InputController.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>

InputController* inp;
void mouseCallback(int button, int state, int x, int y) {
	inp->updateMouse(button, state, x, y);
}
void passiveMouseCallback(int x, int y) {
	inp->updatePassiveMouse(x, y);
}


InputController :: InputController() {
	inp = this;

	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(passiveMouseCallback);
}

int InputController :: getMouseX() {
	return mouseX;
}

int InputController :: getMouseY() {
	return mouseY;
}

		
void InputController :: updateMouse(int button, int state, int x, int y) {
	//bool* leftMouse;
	//bool* middleMouse;
	//bool* rightMouse;
}
void InputController :: updatePassiveMouse(int x, int y) {
	mouseX = x;
	mouseY = y;
}

