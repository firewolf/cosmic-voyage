/*
 * solar-system.cpp
 *
 *  Created on: 29-11-2010
 *      Author: tmroczkowski
 */


#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <vector>

#include "lib/drawing.h"
#include "mesh/Sphere.h"
#include "lib/Colors.h"
#include "math/Math.h"
#include "math/Orbit.h"
#include "planets/Planet.h"
#include "planets/SolarSystem.h"

#include "input/keyboard.h"
#include "input/mouse.h"

using namespace std;


Moving 	 moving;
Keyboard keyboard (&moving);
Mouse  	 mouse (&moving);
Colors   colors;
time_t   rawtime;
tm 		*tm;

SolarSystem *solar;

Sphere sunLight (0., 0., 0., 1, 12, 12, colors.white4f);
Vector3<float> vsunLightPosition = sunLight.getCoords();

float	d = 0;

void solarInit();

void glInit (void) {

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

    glDisable(GL_TEXTURE_1D);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

}

void initLights (void) {
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, colors.white4f);
}

void displayLights(void) {
    glPushMatrix();
    	float sunLightPosition[4] = {vsunLightPosition.x, vsunLightPosition.y, vsunLightPosition.z, 1.};
    	glLightfv(GL_LIGHT0, GL_POSITION, sunLightPosition);
    glPopMatrix();
}


void solarInit() {
	solar = new SolarSystem;
    initLights ();
}

void display (void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    keyboard.handleKeys();

    drawCrossHair ();
    displayLights ();

    solar->draw(d += .01);
    solar->drawUniverse();

	glFlush();
    glutSwapBuffers();

}

void updateSolarSystem(int value) {}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat) w/ (GLfloat) h, 1.0, 1E+6);
    glMatrixMode(GL_MODELVIEW);
    mouse.init();
    cout << "<<<<<<<<<<<<<<<<<< Solar System game, Version 1.2 >>>>>>>>>>>>>>>>>>>>" << endl;
}

/**
 * delegate input
 */
void motion (int x, int y) { mouse.motion(x, y);}
void handleKeypress(unsigned char key, int x, int y) { keyboard.handleKeypress(key, x, y);}
void handleKeyUp(unsigned char key, int x, int y) { keyboard.handleKeyUp(key, x, y);}
void shandleKeypress(int key, int x, int y) { keyboard.shandleKeypress(key, x, y);}
void shandleKeyUp(int key, int x, int y) { keyboard.shandleKeyUp(key, x, y);}

int main (int argc, char** argv) {

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutGameModeString("1680x1050:16@60");
    glutEnterGameMode();
    glutSetCursor(GLUT_CURSOR_NONE);

    glInit () ;
    solarInit();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(motion);
	glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyUp);
    glutSpecialFunc(shandleKeypress);
    glutSpecialUpFunc(shandleKeyUp);
	glutTimerFunc(0, updateSolarSystem, 0);
    glutMainLoop();

    return 0;
}
