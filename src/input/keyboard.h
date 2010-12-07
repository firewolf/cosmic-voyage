
#ifndef INPUT_KEYBOARD_H_INCLUDED
#define INPUT_KEYBOARD_H_INCLUDED

#include "moving.h"
#include <iostream>

using namespace std;

class Keyboard {
	private:

		float deltaMove;
		float tdeltaMove;
		float tdeltaMoveStep;

		int deltaAngle;

		void construct (Moving *moving) {
			deltaMove = 2.;
			deltaAngle = 5;
			this->moving = moving;

			tdeltaMove = 0.;
			tdeltaMoveStep = 0.01;

		}

	public:
		bool keystates[256];
		Moving *moving;

		Keyboard (void) {}
		Keyboard (Moving *moving) {
			this->construct(moving);
		}
		Keyboard (Moving *moving, float deltaMove) : deltaMove(deltaMove) {
			this->construct(moving);
		}

		~Keyboard () {}

		void handleKeys() {

		    if(keystates[27])
		    	exit(0);

		    //rotate up down
		    if(keystates['l']) moving->rotate(deltaAngle, .0f, 1.0f, .0f, 1);
		    if(keystates['j']) moving->rotate(deltaAngle, .0f, 1.0f, .0f, -1);

		    //rotate right left
		    if(keystates['k']) moving->rotate(deltaAngle, 1.0f, .0f, .0f, 1);
		    if(keystates['i']) moving->rotate(deltaAngle, 1.0f, .0f, .0f, -1);

		    //forward/back
		    if(keystates['w']) {

//		    	moving->move(tdeltaMove, .0f, .0f, 1.0f, 1);

		    	if(tdeltaMove < deltaMove)
		    		tdeltaMove += tdeltaMoveStep;

//		    	printf("tdeltaMove: %10.10f\n", tdeltaMove);

		    }

		    if(keystates['s']) {
//		    	if(tdeltaMove > 0)
//		    		tdeltaMove = 0;
//		    	moving->move(deltaMove, .0f, .0f, 1.0f, 1);

		    	if(tdeltaMove > deltaMove * -1)
		    		tdeltaMove -= tdeltaMoveStep;
		    }

		    //straigth right/left
		    if(keystates['d']) moving->moveAndRotate(keystates, deltaMove/8.,-1, 1);
		    if(keystates['a']) moving->moveAndRotate(keystates, deltaMove/8., 1,-1);

		    //rotate in place
		    if(keystates['e']) moving->rotate(deltaAngle * 8, .0f, .0f, 1.0f, 1);
		    if(keystates['q']) moving->rotate(deltaAngle * 8, .0f, .0f, 1.0f, -1);

			if(!keystates['a'] && !keystates['d'] && moving->zrotVect.size() > 0) {
				moving->tiltBack(moving->tiltdir);
			}

			if(!keystates['w'] && tdeltaMove > 0) {
				tdeltaMove -= tdeltaMoveStep;
			}

			if(!keystates['s'] && tdeltaMove < 0) {
				tdeltaMove += tdeltaMoveStep;
			}

			if(tdeltaMove != 0) {
				moving->move(tdeltaMove, .0f, .0f, 1.0f, 1);
			}

			if(keystates['o']) {}
		}

		void oKeyAction() {
			Planet::withOrbit = !Planet::withOrbit;
			cout << "orbit switch off requested " << Planet::withOrbit << endl;
		}

		void handleKeypress(unsigned char key, int xX, int yY) {

			if(key == 'o') oKeyAction();

		    keystates[key] = true;
		}

		void handleKeyUp(unsigned char key, int x, int y) {
		    keystates[key] = false;
		}

		void shandleKeypress(int key, int x, int y) {
			cout << "special pressed: " << key << endl;
			if(key == 101) {
				this->deltaMove += 10;
				std::cout << "throttle: " << this->deltaMove << endl;
			}
			if(key == 103) {
				this->deltaMove -= 10;
				std::cout << "throttle: " << this->deltaMove << endl;
			}
		}

		void shandleKeyUp(int key, int x, int y) {
			cout << "special up: " << key << endl;
		}

};

#endif
