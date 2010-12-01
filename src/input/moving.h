
#ifndef INPUT_MOVING_H_INCLUDED
#define INPUT_MOVING_H_INCLUDED

#include <vector>
#include "../math/Math.h"
#include <iostream>

using namespace std;

class Moving {

	public :

		vector<short> zrotVect;
		short tiltdir;
		short tiltStep;
		GLfloat *TrMatrix;

		Moving (void) : tiltdir(1), tiltStep(4) {
			TrMatrix = new GLfloat[16];
			GLfloat tmpMatrix[16] = {1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f};
			for (register int i = 0; i < 16; i++) TrMatrix[i] = tmpMatrix[i];
		}

		~Moving () {
			delete [] TrMatrix;
		}

		void moveAndRotate(bool *keystates, float dMove, short moveDirection, short td) {

			bool remainingL = !keystates['a'] && zrotVect.size() > 0 && tiltdir != td;
			bool remainingR = !keystates['d'] && zrotVect.size() > 0 && tiltdir != td;

			if(remainingL || remainingR) {
				cout << "remaing called s: " << zrotVect.size() << endl;
				short sum = 0;
				while(!zrotVect.empty()) {
					sum += zrotVect.at(zrotVect.size() - 1);
					zrotVect.pop_back();
				}

				rotate(sum, .0f, .0f, 1.0f, td);
			}

			tiltdir = td;

			move(dMove, 1.0f, .0f, .0f, moveDirection);

			if(zrotVect.size() < 24) {
				zrotVect.push_back(tiltStep);
				rotate(zrotVect.at(zrotVect.size() - 1), .0f, .0f, 1.0f, tiltdir);
			}

		}

		void tiltBack(short tiltdir) {
			rotate(zrotVect.at(zrotVect.size() - 1), .0f, .0f, 1.0f, tiltdir * -1);
			zrotVect.pop_back();
		}

		//direction 1 -1
		void rotate (int angle, float x, float y, float z, int direction) {
			glLoadIdentity();
			glRotatef(Math::RAD(angle) * direction, x, y, z);
			glMultMatrixf(TrMatrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
		}

		//direction 1 -1
		void move (float step, float x, float y, float z, int direction) {
			glLoadIdentity();
			glTranslatef(step * direction * x, step * direction * y, step * direction * z);
			glMultMatrixf(TrMatrix);
			glGetFloatv(GL_MODELVIEW_MATRIX, TrMatrix);
		}


		void debugMatrix(float *matrix) {
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
			for(register int i = 0; i < 4; i++){
				for(register int j = 0; j < 16; j+=4)
					cout << matrix[i + j] << ";";
				cout << endl;
			}
			cout << "--------------------------------" << endl;
		}
};

#endif
