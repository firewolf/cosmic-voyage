

#ifndef LIB_IMAGE_IMAGEFACTORY_H_
#define LIB_IMAGE_IMAGEFACTORY_H_

#include "Image.h"

#include "BMPImage.h"
//#include "Png.h"
#include "Jpeg.h"

enum ImageType {
	JPEG,BMP,PNG
};

class ImageFactory {

private:
	ImageType resolveName(std::string name) {
		ImageType type;

		if(name.find(".jpg")!=string::npos || name.find(".jpeg")!=string::npos)
			type = JPEG;

		std::cout << "found " << type << std::endl;
		if(name.find(".bmp")!=string::npos)
			type = BMP;

		std::cout << "found " << type << std::endl;

		return type;
	}

	Image *resolveTarget(std::string path) {
		Image *image;
		switch(resolveName(path)) {
		case JPEG:
			image = new Jpeg(path);
			break;
		case BMP:
			image = new BMPImage(path);
			break;
//		case PNG:
//			image = new Png(path);
//			break;
		default:
			std::cout << "No image class for path: " << path << std::endl;
		}
		return image;
	}

public:

	ImageFactory () {}
	~ImageFactory () {}

	GLuint load (std::string path) {
		Image *image = resolveTarget(path);
		image->loadTexture2D();
		return image->textureId;
	}


};

#endif
