
#ifndef MESH_SPHERE_H_INCLUDED_
#define MESH_SPHERE_H_INCLUDED_

#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include "../lib/Colors.h"
#include "../math/Math.h"
#include "../math/SphereMath.h"

typedef struct { int x, y, z; double u, v; } Verts;

class Sphere {

	private:
		GLuint glList;

		void construct () {
			radius = 4;
			slices = 36;
			stacks = 36;
			x = 0;
			y = 0;
			z = 0;
			textureId = 0;
			emmision = false;
			rotateAngle = 0;
			glList = 0;
			name = "sphere";
			rotateDelta = 0.;
			std::cout << "ctor called " << this->name << std::endl;
		}

		int create (){

			if(glList != 0) {
				glCallList(glList);
				return 1;
			}

			std::vector<std::vector<Triplet<float> > > triplets;
			SphereMath::create(this->radius, 72, triplets);

        	glList = glGenLists(1);
        	cout << "list generated " << glList << " for " << this->name << " radius: " << this->radius << endl;
        	glNewList(glList,GL_COMPILE);
        		for (register int i = 0, endi = triplets.size(); i < endi; i++) {
        			glBegin(GL_QUAD_STRIP);
        			for (register int j=0, endj = triplets[i].size(); j <= endj;j++) {
						glNormal3f(triplets[i][j].normal.x, triplets[i][j].normal.y, triplets[i][j].normal.z);
						glTexCoord2f(triplets[i][j].texCoords.x, triplets[i][j].texCoords.y);
						glVertex3f(triplets[i][j].vertex.x, triplets[i][j].vertex.y, triplets[i][j].vertex.z);
        			}
    				glEnd();
        		}
        	glEndList();

			return 1;
		}

	protected:
		string name;
		float rotateAngle;

		void enableTexture()  { glEnable(GL_TEXTURE_2D);  }
		void disableTexture() { glDisable(GL_TEXTURE_2D); }
		void enableLights()   { glEnable(GL_LIGHTING);    }
		void disableLights()  { glDisable(GL_LIGHTING);   }

    public :

        float radius;
        int slices;
        int stacks;
        float x;
        float y;
        float z;
        GLuint textureId;
        Colors colors;
        bool emmision;
		float rotateDelta;

        Sphere (void) { construct (); }

        Sphere (float x, float y, float z, float radius, int slices, int stacks) {
        	construct ();
            this->radius = radius;
            this->slices = slices;
            this->stacks = stacks;
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Sphere (float x, float y, float z, float radius, int slices, int stacks, float *color3f) {
        	construct ();
            this->radius = radius;
            this->slices = slices;
            this->stacks = stacks;
            this->x = x;
            this->y = y;
            this->z = z;
        }

        ~Sphere () {}

        void createSphere () {
        	this->createSphere(textureId);
        }

        void createSphere (int texture) {
        	glPushMatrix();
				glTranslatef(x, y, z);
				rotateAngle += rotateDelta;
			    glRotatef(rotateAngle, 0., 1., 0.);
				if(texture != 0) {
					glDisable(GL_BLEND);
					this->enableTexture();
					glBindTexture (GL_TEXTURE_2D, texture);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, colors.white4f);
					glMaterialfv(GL_FRONT, GL_EMISSION, this->emmision == true ? colors.white4f : colors.black4f);
				}

        		this->create();

    			if(texture != 0)
    				this->disableTexture();

        	glPopMatrix();
        }

    	Vector3<float> getCoords () {
    		return
    				Vector3<float>(x, y, z);
    	}
};

#endif
