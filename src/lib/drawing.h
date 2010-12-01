
#ifndef DRAWING_H_INCLUDED_
#define DRAWING_H_INCLUDED_

#include "Colors.h"
#include "../mesh/Sphere.h"

struct Textures {
	GLuint sun, earth;
};

extern Sphere earth;
extern Sphere sun;
extern Sphere mars;
extern Sphere earthMoon;

void drawTunnel();
void drawAxis (void);
void drawQuad(float vertices[12], int r, int g, int b);
void drawTriangle();
void drawSolarSystem(float rangle, Textures textures, Colors colors, int angle);
void drawTunnel2 ();
void drawColoredQuad(float vertices[12]);
void drawCrossHair() ;

#endif
