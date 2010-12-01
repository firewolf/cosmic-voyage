/*
 * Png.h
 *
 *  Created on: 29-11-2010
 *      Author: tmroczkowski
 */

#ifndef PNG_H_
#define PNG_H_

#include "Image.h"
#include <png.h>
#include <iostream>


	png_voidp user_error_ptr () {
		return NULL;
	}

	void user_error_fn (png_struct*, const char*) {

	}

	void user_warning_fn (png_struct*, const char*) {

	}

class Png: public Image {
public:

	Png(std::string filename) :
		Image(filename) {}

	virtual ~Png() {}

	bool load(const char *source) {

		FILE *fp = fopen(source, "rb");
		if (!fp) {
			std::cout << "file error" << std::endl;
			return false;
		}

		int number = 8;
		png_byte *header = new png_byte[8];
		fread(header, 1, number, fp);
		bool is_png = !png_sig_cmp(header, 0, number);

		if (!is_png) {
			std::cout << "this file is not png file" << std::endl;
			return false;
		}

		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)&user_error_ptr, &user_error_fn, &user_warning_fn);

		if (!png_ptr) {
			std::cout << "some error with png file" << std::endl;
			return false;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			std::cout << "some error with png file" << std::endl;
			return false;
		}

		png_infop end_info = png_create_info_struct(png_ptr);

		if (!end_info) {
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			std::cout << "some error with png file" << std::endl;
			return false;
		}

		width            = png_get_image_width(png_ptr, info_ptr);
		height           = png_get_image_height(png_ptr, info_ptr);
		bpp        		 = png_get_bit_depth(png_ptr, info_ptr);
		int color_type       = png_get_color_type(png_ptr, info_ptr);

//		filter_method    = png_get_filter_type(png_ptr, info_ptr);
//		compression_type = png_get_compression_type(png_ptr, info_ptr);
//		interlace_type   = png_get_interlace_type(png_ptr, info_ptr);

		type = GL_RGB;
		if(color_type == 4) {
			type = GL_RGBA;
		}

		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, number);

		int png_transforms = 0;

		png_read_png(png_ptr, info_ptr, png_transforms, NULL);

		png_bytep **row_pointers[height] = new png_byte*[height];
		row_pointers = png_get_rows(png_ptr, info_ptr);

//		int pixel_size = 3;

//		if (height > PNG_UINT_32_MAX/png_sizeof(png_byte))
//			png_error (png_ptr, "Image is too tall to process in memory");
//
//		if (width > PNG_UINT_32_MAX/pixel_size)
//			png_error (png_ptr, "Image is too wide to process in memory");
//
//		(void*) row_pointers = png_malloc(png_ptr, height*png_sizeof(png_bytep));
//
//		for (int i=0; i<height; i++) row_pointers[i]=NULL;  /* security precaution */
//		for (int i=0; i<height; i++) row_pointers[i]=png_malloc(png_ptr, width * pixel_size);


		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);

		return true;
	}
};

#endif /* PNG_H_ */
