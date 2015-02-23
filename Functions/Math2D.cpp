// Math2D.cpp


#include <cmath>
#include "Math2D.h"

float calcLenX(float len, float dir) {
	return len * cos(dir/180*PI);
}

float calcLenY(float len, float dir) {
	return - len * sin(dir/180*PI);
}
