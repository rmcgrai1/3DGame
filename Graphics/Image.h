// Image.h
// Ryan McGrail

#ifndef IMAGE_H
#define IMAGE_H

#define cimg_use_png

#include <string>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

class Image {
	public:
		Image(string);								// Constructor
		int getWidth();								// Getting Image Width
		int getHeight();							// Getting Image Height
		void* getData();							// Getting Image Data Buffer
		int getValue(int, int);						// Getting Grayscale Value of Pixel
		void interleave(unsigned char*);			// Interleaving RGBA Data for OpenGL

	private:
		CImg<unsigned char> image;					// CImg Image

		int width;									// Width
		int height;									// Height
};

#endif


