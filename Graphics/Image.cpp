// Image.cpp
// Ryan McGrail

#define cimg_use_png
#include <iostream>
#include "Image.h"
#include <string>
#include "CImg.h"
#include "../Global.h"
using namespace cimg_library;
using namespace std;


// Constructor
Image :: Image(string fileName) {

	// Load In Image
	image = CImg<>(fileName.c_str()).normalize(0,255);

	// Store Width/Height
	width = image.width();
	height = image.height();
}

// Get Width of Image
int Image :: getWidth() {
	return width;
}

// Get Height of Image
int Image :: getHeight() {
	return height;
}

// Interleave Image Channels
void Image :: interleave(unsigned char* out) {
	// CImg loads images into a one-dimensional array, with all channels separate from each other.
	// For an Image with all four channels, this looks like:
	// RRR...RRR|GGG...GGG|BBB...BBB|AAA...AAA
	
	// However, OpenGL requires that the data be INTERLEAVED. For the above example, this looks like:
	// RGBA|RGBA|RGBA...RGBA|RGBA|RGBA
	
	// This function is REQUIRED for OpenGL to properly display images.

	unsigned char* data = image.data();
	int i, numChannels;
	i = 0;
	
	// Get Number of Channels (Grayscale, Grayscale and Alpha, RGB, Or RGBA)
	numChannels = image.spectrum();

	// If One Channel, Only Grayscale, no Alpha
	if(numChannels == 1) {
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) {

				// Interleave RGB (All Same Value)
				for(int c = 0; c < 3; c++)
					out[i+c] = image(x,y,0);
				
				// Assume Opaque
				out[i+3] = 255;

				i += 4;
			}
	}

	// If Two Channels, Grayscale and Alpha
	else if(numChannels == 2) {
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) {
			
				// Interleave RGB (All Same Value)
				for(int c = 0; c < 3; c++)
					out[i+c] = image(x,y,0);

				// Get Alpha
				out[i+3] = image(x,y,1);

				i += 4;
			}
	}
	// If Three Channels, Only RGB
	else if(numChannels == 3) {
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) {

				// Interleave RGB
				for(int c = 0; c < 3; c++)
					out[i+c] = image(x,y,c);

				// Assume Full Alpha (Opaque)
				out[i+3] = 255;

				i += 4;
			}
	}
	// If Four Channels, RGBA
	else if(numChannels == 4) {
		for(int y = 0; y < height; y++)
			for(int x = 0; x < width; x++) {

				// Interleave RGBA
				for(int c = 0; c < 4; c++)
					out[i+c] = image(x,y,c);

				i += 4;
			}
	}
}

// Get Image Data Buffer
void* Image :: getData() {
	return image.data();
}

// Get Value of Pixel at Position (for Grayscale)
int Image :: getValue(int x, int y) {
	if(image.spectrum() == 1)
		return image(x,y,0);
	else
		return .21*image(x,y,0) + .72*image(x,y,1) + .07*image(x,y,2);
}