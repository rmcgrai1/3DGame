// Image.cpp


#include "Image.h"
#include <string>
#include "CImg.h"
using namespace cimg_library;
using namespace std;


Image :: Image(string fileName, int argc, char** argv) {

	const char* file_i = cimg_option("-i",fileName.c_str(),"Input image");
	//image = CImg<>(file_i).normalize(0,255);
}

int Image :: getWidth() {
	return image.width();
}

int Image :: getHeight() {
	return image.height();
}

void* Image :: getData() {
	return image.data();
}

void Image :: getPixelData() {
	//R = image(x,y,0)
	//G = image(x,y,1)
	//B = image(x,y,2)
}
