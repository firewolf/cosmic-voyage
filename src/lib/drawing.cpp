
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include "Colors.h"
#include "drawing.h"

float bottomFace [] = {
	-1, -1,  -1,
	 1, -1,  -1,
	 1, -1,  1,
	-1, -1,  1
};
float backFace [] = {
	-1,  1,  -1,
	 1,  1,  -1,
	 1, -1,  -1,
	-1, -1,  -1
};
float leftFace  [] = {
	-1,  1,  -1,
	-1, -1,  -1,
	-1, -1,  1,
	-1,  1,  1
};
float topFace [] = {
	-1,  1,  -1,
	 1,  1,  -1,
	 1,  1,  1,
	-1,  1,  1
};
float rightFace [] = {
	 1,  1,  -1,
	 1, -1,  -1,
	 1, -1,  1,
	 1,  1,  1
};
float frontFace  [] = {
	-1,  1,  1,
	 1,  1,  1,
	 1, -1,  1,
	-1, -1,  1
};


void drawTunnel();
void drawAxis (void);
void drawQuad(float vertices[12], int r, int g, int b);
void drawTriangle();

void drawTunnelBoxF ();
void drawTunnelBoxR ();

void drawQuad(float vertices[12], int r, int g, int b) {

	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(vertices[0], vertices[1], vertices[2]);
		glVertex3f(vertices[3], vertices[4], vertices[5]);
		glVertex3f(vertices[6], vertices[7], vertices[8]);
		glVertex3f(vertices[9], vertices[10], vertices[11]);
	glEnd();

}

void drawColoredQuad(float vertices[12]) {

	glBegin(GL_QUADS);
		glColor3f(255, 0, 0);
		glVertex3f(vertices[0], vertices[1], vertices[2]);
		glColor3f(0, 255, 0);
		glVertex3f(vertices[3], vertices[4], vertices[5]);
		glColor3f(0, 0, 255);
		glVertex3f(vertices[6], vertices[7], vertices[8]);
		glColor3f(255, 0, 255);
		glVertex3f(vertices[9], vertices[10], vertices[11]);
	glEnd();

}

void drawTunnel () {
    glPushMatrix();
		glTranslatef(14.0f, 1.0f, .0f);
		glScalef(3.0f, 2.0f, 24.0f);
		drawQuad(leftFace, 255, 0, 0);
		drawQuad(topFace, 0, 255, 255);
		drawQuad(rightFace, 0, 255, 0);
		drawQuad(bottomFace, 255, 255, 0);

//		drawQuad(backFace, 255, 255, 255);
//		drawQuad(frontFace, 0, 0, 255);

    glPopMatrix();
}
void drawTunnelBoxF () {
	drawColoredQuad(leftFace);
	drawColoredQuad(topFace);
	drawColoredQuad(rightFace);
	drawColoredQuad(bottomFace);
}

void drawTunnelBoxR () {
	float bFace [] = {
			 1, -1,  1,
			-1, -1,  1,
			 2, -1, -2,
			 2, -1,  0
	};
	float lFace  [] = {
			-1, -1,  1,
			 2, -1, -2,
			 2,  1, -2,
			-1,  1,  1,
	};
	float tFace [] = {
			 1,  1,  1,
			-1,  1,  1,
			 2,  1, -2,
			 2,  1,  0
	};
	float rFace [] = {
			 1, -1,  1,
			 1, 1,  1,
			 2, 1,  0,
			 2, -1,  0
	};

	drawColoredQuad(bFace);
	drawColoredQuad(lFace);
	drawColoredQuad(tFace);
	drawColoredQuad(rFace);
}

void drawTunnel2 () {
	glPushMatrix();

		glTranslatef(-20.0f, 4.0f, .0f);
		glScalef(2.0f, 2.0f, 2.0f);
		glRotatef(90, 1.0f, .0f, .0f);
		drawTunnelBoxF ();
		glTranslatef(.0f, .0f, -2.0f);
		drawTunnelBoxR ();
		glTranslatef(3.0f, .0f, -1.0f);
		glRotatef(90, .0f, 1.0f, .0f);
		drawTunnelBoxF ();
		glTranslatef(.0f, .0f, 2.0f);
		drawTunnelBoxF ();
	glPopMatrix();
}

void drawTriangle() {
    glPushMatrix();
    	glTranslatef(.0f, .0f, 40.0f);
		drawAxis();
		glBegin(GL_TRIANGLES);

			glColor3f(1.0f,0.0f,0.0f);// Red
			glVertex3f( 0.0f, 0.0f, -1.0f);// Top Of Triangle (Front)
			glVertex3f( 1.0f, 1.0f, 1.0f);// Right Of Triangle (Front)
			glVertex3f( 1.0f,-1.0f, 1.0f);// Left Of Triangle (Front)

			glColor3f(0.0f,1.0f,0.0f);// Red
			glVertex3f( 0.0f, 0.0f,-1.0f);// Top Of Triangle (Right)
			glVertex3f( -1.0f, 1.0f, 1.0f);// Right Of Triangle (Right)
			glVertex3f( -1.0f,-1.0f, 1.0f);// Left Of Triangle (Right)

			glColor3f(0.0f,0.0f,1.0f);// Red
			glVertex3f( 0.0f, 0.0f,-1.0f);// Top Of Triangle (Back)
			glVertex3f( 1.0f,-1.0f, 1.0f);// Right Of Triangle (Back)
			glVertex3f(-1.0f,-1.0f, 1.0f);// Left Of Triangle (Back)

			glColor3f(1.0f,1.0f,1.0f);// Red
			glVertex3f( 0.0f, 0.0f,-1.0f);// Top Of Triangle (Left)
			glVertex3f( 1.0f, 1.0f, 1.0f);// Right Of Triangle (Left)
			glVertex3f(-1.0f, 1.0f, 1.0f);// Left Of Triangle (Left)
		glEnd();// Done Drawing The Pyramid
    glPopMatrix();
}

void drawAxis (void) {

    glPushMatrix();
    glBegin(GL_LINES);
        glColor3f(1.0f, .0f, .0f);
        glVertex3f(.0f, .0f, -60.0f);
        glVertex3f(.0f, .0f,  10.0f);

        for(register int i = 10; i >= -60; i--) {
            glColor3f(1.0f, .0f, .0f);
            glVertex3f(.0f, .1f, i);
            glVertex3f(.0f, .0f, i);
        }

        glColor3f( .0f, .0f, 1.0f);
        glVertex3f(-20.0f, .0f, .0);
        glVertex3f( 20.0f, .0f, .0);

        glColor3f( .0f, 1.0f, .0f);
        glVertex3f(.0f, -100.0f, .0f);
        glVertex3f(.0f,  100.0f, .0f);

        for(register int i = -100; i < 100; i+=10) {
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, i, .0f);
            glVertex3f(.0f,  i, .0f);
        }

    glEnd();
    glPopMatrix();

}

void drawCrossHair() {
    glPushMatrix();
    	glLoadIdentity();
        glBegin(GL_LINES);
        glColor3f(.4f, .4f, .4f);
        glVertex3f(-.005f,.0f, -1.f);
        glVertex3f( .005f,.0f, -1.f);
        glVertex3f( .0f, .005f, -1.f);
        glVertex3f( .0f,-.005f, -1.f);
        glEnd();
    glPopMatrix();
}

