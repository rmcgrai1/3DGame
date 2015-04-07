// Math2D.h


#ifndef MATH2D_H
#define MATH2D_H

#define PI 3.14159265


// BASIC
	float sqr(float);

// GEOMETRIC
	float calcPtDis(float, float, float, float);

// TRIG
	float calcLenX(float, float);
	float calcLenY(float, float);
	float calcPtDir(float, float, float, float);

	float modf(float, float);


	float rnd();
	unsigned long getTime();

// MAGICAL!!
	float calcTurnToDir(float, float);
	float calcAngleDiff(float, float);

#endif
