// Math2D.cpp


#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include "Math2D.h"
using namespace std::chrono;



// BASIC
	float min(float a, float b) {
		return (a < b) ? a : b;
	}
	float max(float a, float b) {
		return (a > b) ? a : b;
	}
	float sqr(float x) {
		return x*x;
	}
	float sign(float x) {
		if(x == 0)
			return 0;
		else return (x > 0) ? 1 : -1;
	}
	float contain(float mi, float x, float ma) {
		return max(mi, min(x, ma));
	}


// RANDOM
	float rnd() {
		return ((getTime()*rand())%1000)/1000.;
	}
	float rnd(float cap) {
		return rnd()*cap;
	}
	float rnd(float mi, float ma) {
		return mi + rnd(ma-mi);
	}
	unsigned long getTime() {

		nanoseconds ms = duration_cast< nanoseconds >(
	 		high_resolution_clock::now().time_since_epoch()
		);

		return ms.count();
	}


// GEOMETRIC
	float calcPtDis(float x1, float y1, float x2, float y2) {
		return sqrt(sqr(x2-x1) + sqr(y2-y1));
	}
	float calcLineDis(float x, float y, float x1, float y1, float x2, float y2) {
		float x0, y0;
		float dx, dy, t;

		dx = x2 - x1;
		dy = y2 - y1;
		if ((dx == 0.) && (dy == 0.)) {
			x0 = x1;
			y0 = y1;
		}
		else {
			t = (dx*(x-x1) + dy*(y-y1)) / (dx*dx+dy*dy);
				t = contain(0,t,1);
			x0 = x1 + t * dx; 
			y0 = y1 + t * dy;
		}
	
		return calcPtDis(x, y, x0, y0);
	}

// TRIG
	float calcLenX(float len, float dir) {
		return len * cos(dir/180*PI);
	}

	float calcLenY(float len, float dir) {
		return len * sin(dir/180*PI);
	}

	float calcPtDir(float x1, float y1, float x2, float y2) {
		return atan2(y2-y1, x2-x1)/PI*180;
	}
	float calcLineDir(float x, float y, float x1, float y1, float x2, float y2) {
		float x0, y0;
		float dx, dy, t;

		dx = x2 - x1;
		dy = y2 - y1;
		if ((dx == 0.) && (dy == 0.)) {
			x0 = x1;
			y0 = y1;
		}
		else {
			t = (dx*(x-x1) + dy*(y-y1)) / (dx*dx+dy*dy);
				t = contain(0,t,1);
			x0 = x1 + t * dx; 
			y0 = y1 + t * dy;
		}
	
		return calcPtDir(x0, y0, x, y);
	}

	float modf(float x, float y) {
		if(x == y)
			return 0;
		else if(x < y)
			return x;
		else {
			int t = 0;

			while(y < x)
				x -= y;

			return x;
		}
	}


// MAGICAL!!!
	float calcTurnToDir(float dir, float toDir) {
		float newDir = 0;
		
		if(fabs(fmod(fmod(toDir - dir, 360.) + 540., 360.) - 180) >= 160)
			newDir += sin((toDir-dir)/180*PI)*16*15;

		newDir += sin((toDir-dir)/180*PI)*8;
		return newDir;
	}

	float calcAngleDiff(float dir1, float dir2) {
		return modf((modf(dir1 - dir2, 360) + 540), 360) - 180;
	}

/*float abs(float n) {
	return (n > 0) ? n : -n;
}*/
