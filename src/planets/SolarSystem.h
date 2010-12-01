/*
 * SolarSystem.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef SOLARSYSTEM_H_
#define SOLARSYSTEM_H_

#include <time.h>
#include <string.h>

#include "Sun.h"
#include "PlanetData.h"

#include "../math/Math.h"
#include "../lib/Colors.h"
#include "../lib/drawing.h"

class SolarSystem {

private:

	GLuint glUniverseListId;

	void construct () {
		glUniverseListId = 0;
	}
public:

	Orbit  *orbit;
	Sun sun;
	Planet earth;
	Planet mercury;
	Planet venus;
	Planet emoon;
	Planet mars;
	Planet jupiter;
	Planet saturn;
	Planet uran;
	Planet neptun;
	Planet pluton;

	SolarSystem() :
		orbit(Orbit::getInstance())
	{
		this->earth = Planet(&earthd);
		this->mercury = Planet(&mercuryd);
		this->venus = Planet(&venusd);
		this->emoon = Planet(&emoond, false);
		this->mars = Planet(&marsd);
		this->jupiter = Planet(&jupiterd);
		this->saturn = Planet(&saturnd);
		this->uran = Planet(&urand);
		this->neptun = Planet(&neptund);
		this->pluton = Planet(&plutond);
		construct ();
	};

	void draw(double d) {
			sun.run(d);
			mercury.run(d);
			venus.run(d);
			earth.run(d);
			emoon.pd->center = earth.getCoords();
			emoon.run(d);
			mars.run(d);
			jupiter.run(d);
			saturn.run(d);
			uran.run(d);
			neptun.run(d);
			pluton.run(d);
	}

	void initImage (Image *image, GLuint &textureId) {
		image->loadTexture2D();
		textureId = image->textureId;
	}


	int drawUniverse () {
		glPushMatrix();
		generateUniverse();
		glPopMatrix();
		return 1;
	}

	int generateUniverse() {

			if(glUniverseListId != 0) {
				glCallList(glUniverseListId);
				return 1;
			}

			glUniverseListId = glGenLists(1);
			glNewList(glUniverseListId,GL_COMPILE);
				glColor4f(.7, .7, .7, 1.);
				makeStars(9E+5);
				makeStars(1E+6);
        	glEndList();

		return 1;
	}

	void makeStars(int radius) {
		float x, y, z;
		int theta, phi;
		srand (time (NULL));
		glBegin(GL_POINTS);

			for(register int i = 0; i < 1000; i++) {
				theta = Math::randm(360);
				phi = (Math::randm(181) - 90);
				x = radius * cos(theta) * cos(phi);
				y = radius * cos(theta) * sin(phi);
				z = radius * sin(theta);

				glVertex3f(x, y, z);

			}
		glEnd();
	}

	virtual ~SolarSystem() {};

};

#endif /* SOLARSYSTEM_H_ */
