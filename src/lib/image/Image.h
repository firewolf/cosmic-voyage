

#ifndef LIB_IMAGES_H_
#define LIB_IMAGES_H_

#include <cstring>
#include <stdio.h>
#include <jerror.h>
#include <GL/gl.h>

using namespace std;

class Image {
public:

	unsigned long 		width;
	unsigned long 		height;
	unsigned short int 	bpp; //bits per pixels   unsigned short int
	char 				*pixels;             //the data of the image
	unsigned long 		size;     //length of the file
	int 				channels;      //the channels of the image 3 = RGA 4 = RGBA
	GLuint 				type;
	GLuint 				textureId;
	std::string 		path;

	Image () {}
	Image (std::string filename) :
		path(filename) {}

	~Image () {
		delete []pixels;
	}

	void loadTexture2D() {
		this->load(this->path.c_str());
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, this->type, this->width, this->height, 0, this->type, GL_UNSIGNED_BYTE, this->pixels);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	}

	virtual bool load (const char* filename) {
		return false;
	};
};


#endif
