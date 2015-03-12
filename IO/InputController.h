//InputController.h

#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <map>
using namespace std;

class InputController {

	public:
		InputController();
		void updateMouse(int,int,int,int);
		void updatePassiveMouse(int,int);
		void updateKeyboard(unsigned char, int, int);
		void updateKeyboardUp(unsigned char, int, int);
		void updateKeyboardSpecial(int, int, int);

		bool checkLeftMouse();
		bool checkRightMouse();

		bool checkLetter(char);
		void setLetter(char, bool);
		bool getShift();
		float getWASDDir();
		bool checkWASD(char);
		void setWASD(char, bool);

		int getMouseX();
		int getMouseY();

	private:
		static InputController* mainInp;

		bool* wasdArray;
		bool* letterArray;
		bool* mouseArray;

		int mouseX;
		int mouseY;

		bool isShiftDown;
};

#endif
