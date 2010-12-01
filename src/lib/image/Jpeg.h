/*
 * Jpeg.h
 *
 *  Created on: 25-11-2010
 *      Author: tmroczkowski
 */

#ifndef JPEG_H_
#define JPEG_H_

#include "Image.h"
#include <jpeglib.h>

class Jpeg : public Image {
public:
	Jpeg () {}
	~Jpeg() {}
	Jpeg (std::string filename) : Image(filename) {
	}
	bool load (const char* filename) {
		return this->load(filename, true);
	};

	bool load(const char* FileName, bool Fast = true) {
	  FILE* file = fopen(FileName, "rb");  //open the file
	  struct jpeg_decompress_struct info;  //the jpeg decompress info
	  struct jpeg_error_mgr err;           //the error handler

	  info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
	  jpeg_create_decompress(&info);       //sets info to all the default stuff

	  //if the jpeg file didnt load exit
	  if(!file) {
		fprintf(stderr, "Error reading JPEG file %s!!!", FileName);
		return false;
	  }

	  jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

	  jpeg_read_header(&info, TRUE);   //tell it to start reading it

	  //if it wants to be read fast or not
	  if(Fast)
	  {
		info.do_fancy_upsampling = FALSE;
	  }

	  jpeg_start_decompress(&info);    //decompress the file

	  //set the x and y
	  width = info.output_width;
	  height = info.output_height;
	  channels = info.num_components;

	  type = GL_RGB;

	  if(channels == 4)
	  {
		type = GL_RGBA;
	  }

	  bpp = channels * 8;

	  size = width * height * 3;

	  //read turn the uncompressed data into something ogl can read
	  pixels = new char[size];      //setup data for the data its going to be handling

	  char *p1 = pixels;
	  char **p2 = &p1;
	  int numlines = 0;

	  while(info.output_scanline < info.output_height) {
		numlines = jpeg_read_scanlines(&info, (JSAMPROW*) p2, 1);
		*p2 += numlines * 3 * info.output_width;
	  }

	  jpeg_finish_decompress(&info);   //finish decompressing this file

	  fclose(file);                    //close the file

	  return true;
	}

};

#endif /* JPEG_H_ */
