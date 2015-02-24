// Math2D.cpp


#include <cmath>
#include "Math2D.h"

float calcLenX(float len, float dir) {
	return len * cos(dir/180*PI);
}

float calcLenY(float len, float dir) {
	return len * sin(dir/180*PI);
}


float calcPtDir(float x1, float y1, float x2, float y2) {
	return atan2(y2-y1, x2-x1)/PI*180;
}

float calcTurnToDir(float dir, float toDir) {
	float newDir = 0;
		
	if(fabs(fmod(fmod(toDir - dir, 360.) + 540., 360.) - 180) >= 160)
		newDir += sin((toDir-dir)/180*PI)*16*15;

	newDir += sin((toDir-dir)/180*PI)*8;
	return newDir;
}

/*float abs(float n) {
	return (n > 0) ? n : -n;
}*/
