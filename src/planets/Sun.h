/*
 * Sun.h
 *
 *  Created on: 20-11-2010
 *      Author: tmroczkowski
 */

#ifndef SUN_H_
#define SUN_H_

#include "Planet.h"

class Sun: public Planet {
public:
	Sun() {
		this->radius 		= 109 * 2;
        this->emmision 		= true;
		this->name 			= "sun";
		this->textureId 	= imageFactory->load(std::string("./resources/textures/medres/gstar.jpg"));
	};

	int run (double d) {
		enableLights();
		this->createSphere();
    	this->rotateAngle += .1;
    	disableLights();
		return 0;
	}

	virtual ~Sun() {};
};

#endif /* SUN_H_ */
