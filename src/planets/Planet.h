/*
 * Planet.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef PLANET_H_
#define PLANET_H_

#include "../mesh/Sphere.h"
#include "../lib/image/ImageFactory.h"

class Planet: public Sphere {
private:
	int glOrbitList;
	int scale;
    bool drawOrbit;
protected:

	Orbit *orbit;

    void construct () {
    	orbit = Orbit::getInstance();
    	glOrbitList = 0;
    	scale = 15 * 100;
		imageFactory = new ImageFactory;
    }

public:

    PlanetData *pd;
    ImageFactory *imageFactory;
    static bool withOrbit;

	Planet() {this->construct();};

	Planet(PlanetData *pd, bool drawOrbit = true) : drawOrbit(drawOrbit) {

		this->pd = pd;
		this->construct();

		rotateDelta = pd->rotateDelta;
		radius 	    = pd->radius * 24;

		pd->textureId = imageFactory->load(pd->texturePath);

	}

	virtual int run (double time) {

		if(drawOrbit /*  && withOrbit */)
			this->drawOrbitList();

		Vector3<float> coord = orbit->generateOrbit(pd, time);

		x = pd->center.x + coord.x * scale;
		y = pd->center.y + coord.z * scale;
		z = pd->center.z + coord.y * scale;

		enableLights();
		this->createSphere(pd->textureId);
		disableLights();

		return 1;
	}

	virtual ~Planet() {};

	int drawOrbitList () {

		if(glOrbitList != 0) {
			glCallList(glOrbitList);
			return 1;
		}

//		float orbitMaterial[4] = {.8, .6, .3, .0};
		glOrbitList = glGenLists(1);
		Vector3<float> p;
		double deltai = pd->period / 180. == 0 ? 1 : pd->period / 180.;
		std::cout << pd->name << " deltai: " << pd->period / 720. << std::endl;

		glNewList(glOrbitList,GL_COMPILE);
			glPushMatrix();
				glBegin(GL_POINTS);
					glColor4f(.3, .3, .0, 1.);
					for (double i = 0; i < pd->period; i += deltai) {

						p = orbit->generateOrbit(pd, i);

						x = pd->center.x + p.x * scale;
						z = pd->center.y + p.y * scale;
						y = pd->center.z + p.z * scale;

						glVertex3f(x, y, z);
					}
				glEnd();
			glPopMatrix();
		glEndList();

		return 1;
	}

};

#endif /* PLANET_H_ */
