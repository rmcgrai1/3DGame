// Math2D.cpp
// Ryan McGrail


#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include "Math2D.h"
using namespace std::chrono;


// BASIC
	// Minimum of 2 Floats
	float min(float a, float b) {
		return (a < b) ? a : b;
	}
	
	// Maximum of 2 Floats
	float max(float a, float b) {
		return (a > b) ? a : b;
	}
	
	// Square of a Number
	float sqr(float x) {
		return x*x;
	}
	
	// Sign of Number
	float sign(float x) {
		if(x == 0)
			return 0;
		else return (x > 0) ? 1 : -1;
	}
	
	// Keep Number in Range
	float contain(float mi, float x, float ma) {
		return max(mi, min(x, ma));
	}
	
	// Calculate Speed with Acceleration and deltaX
	// v^2 = 2*a*deltaX
	float calcSpeed(float acceleration, float deltaX) {
		return sqrt(abs(2*acceleration*deltaX));
	}


// RANDOM
	// Get Random Float from 0 to 1
	float rnd() {
		return ((getTime()*rand())%1000)/1000.;
	}
	// Get Random Float from 0 to cap 
	float rnd(float cap) {
		return rnd()*cap;
	}
	// Get Random Float in Range
	float rnd(float mi, float ma) {
		return mi + rnd(ma-mi);
	}
	
	// Get Unix Epoch in Nanoseconds
	unsigned long getTime() {

		nanoseconds ns = duration_cast< nanoseconds >(
	 		high_resolution_clock::now().time_since_epoch()
		);

		return ns.count();
	}


// GEOMETRIC

	// Calculate 2D Distance Between 2 Points
	float calcPtDis(float x1, float y1, float x2, float y2) {
		return sqrt(sqr(x2-x1) + sqr(y2-y1));
	}
	
	// Determine Nearest Point on Line Segment from Given Point 
	void calcLinePt(float x, float y, float x1, float y1, float x2, float y2, float &x0, float &y0) {
		
		float dx, dy, t;

		// Calculate deltaX, deltaY
		dx = x2 - x1;
		dy = y2 - y1;
		
		// If Line is Only a Point, Return Point
		if ((dx == 0.) && (dy == 0.)) {
			x0 = x1;
			y0 = y1;
		}
		// Otherwise, Find Nearest Point on Line Segment
		else {
			// Get Percentage of Nearest Point along Line
			t = (dx*(x-x1) + dy*(y-y1)) / (dx*dx+dy*dy);
			
			// Limit Point to Line Segment
			t = contain(0,t,1);
				
			// Calculate Pt on Line
			x0 = x1 + t * dx; 
			y0 = y1 + t * dy;
		}
	}
	
	// Calculate Distance from Point to Line Segment
	float calcLineDis(float x, float y, float x1, float y1, float x2, float y2) {
		float x0, y0;
		
		// Find Point on Line Nearest to Given Point
		calcLinePt(x, y, x1, y1, x2, y2, x0, y0);

		// Return Distance Between Points
		return calcPtDis(x, y, x0, y0);
	}

// TRIG
	// Calculate X Distance Along Direction
	float calcLenX(float len, float dir) {
		return len * cos(dir/180*PI);
	}

	// Calculate Y Distance Along Direction
	float calcLenY(float len, float dir) {
		return len * sin(dir/180*PI);
	}

	// Calculate Direction from First Point to Second Point
	float calcPtDir(float x1, float y1, float x2, float y2) {
		return atan2(y2-y1, x2-x1)/PI*180;
	}
	
	// Calculate Direction Line to Point
	float calcLineDir(float x, float y, float x1, float y1, float x2, float y2) {
		float x0, y0;
		
		// Find Point on Line Nearest to Given Point
		calcLinePt(x, y, x1, y1, x2, y2, x0, y0);

		// Return Direction Between Points	
		return calcPtDir(x0, y0, x, y);
	}

	// Modulus Function for Floats (Makes Things Simpler)
	float mod(float x, float y) {
		return fmod(x, y);
	}


// Angle Functions

	// Calculate # to Smoothly Rotate 
	float calcTurnToDir(float dir, float toDir) {
		float newDir = 0;
		
		// If Angle Difference Near 180, Need to Add Extra to "Jump Start"
		if(abs(calcAngleDiff(toDir, dir)) >= 160)
			newDir += sin((toDir-dir)/180*PI)*16*15;

		// Add Amt to Rotate Smoothly
		newDir += sin((toDir-dir)/180*PI)*8;
		return newDir;
	}

	// Find Absolute Angle Difference Between 2 Angles
	// Ex: 720-360 = 0
	float calcAngleDiff(float dir1, float dir2) {
		return modf(modf(dir1 - dir2, 360) + 540, 360) - 180;
	}
