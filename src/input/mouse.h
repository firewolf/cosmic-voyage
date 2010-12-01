
#ifndef INPUT_MOUSE_H_
#define INPUT_MOUSE_H_

#include <iostream>

using namespace std;

class Mouse {
	private:
		int lastx, lasty, warpCheck, factor, wHeight, wWidth, mcValue, middleX, middleY, yBound, xBound, warpX, warpY, stopField;
		Moving *moving;
		void debug(int dx, int dy, int x, int y, int lastx, int lasty) {
			cout << "dx: " << dx << ", dy: " << dy << ", x: " << x << ", y: " << y << ", lastx: " << lastx << ", lasty: " << lasty << endl;
		}
		void move (int dx, int dy) {
			moving->rotate(dy * factor, 1.0f, .0f, .0f, 1);
			moving->rotate(dx * factor, .0f, 1.0f, .0f, 1);
		}

		void setNewMousePosition(int x, int y) {
			warpCheck = 1;
			warpX = x;
			warpY = y;
			glutWarpPointer(x, y);
		}

	public:

		Mouse (void) : lastx (-1), lasty(-1), warpCheck(0), factor(16), mcValue (120) {

		}

		Mouse (Moving *moving) : lastx (-1), lasty(-1), warpCheck(0), factor(16), mcValue (120) {
			this->moving = moving;
		}

		void setMcValue(int mcValue){
			this->mcValue = mcValue;
		}

		~Mouse () {}

		void init () {
			wWidth  = glutGet(GLUT_WINDOW_WIDTH);
			wHeight = glutGet(GLUT_WINDOW_HEIGHT);
			middleX = wWidth / 2;
			middleY = wHeight / 2;
			yBound = wHeight - mcValue;
			xBound = wWidth - mcValue;
		}

		void motion(int x, int y) {

			int dx = (x - lastx);
			int dy = (y - lasty);
			lastx = x; lasty = y;

			if(warpCheck == 1) {
//				cout << "---- warpCheck called ----";
//				debug(dx, dy, x, y, lastx, lasty);
				warpCheck = 0;
				return;
			}

			if((lastx == -1) && lasty == -1) {
//				cout << "---- init mouse ----" << endl;
				setNewMousePosition(middleX, middleY);
				return ;
			}

			if(dx < -400 || dx > 400 || dy > 400 || dy < -400)
				return ;

			this->move(dx, dy);
			this->checkMouse (x, y);

		}

		void checkMouse (int x, int y) {
			if (y > yBound)  setNewMousePosition(x, mcValue);
			if (y < mcValue) setNewMousePosition(x, yBound);
			if (x > xBound)  setNewMousePosition(mcValue, y);
			if (x < mcValue) setNewMousePosition(xBound,  y);
		}
};

#endif
