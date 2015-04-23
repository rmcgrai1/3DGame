// Math2D.h
// Ryan McGrail


#ifndef MATH2D_H
#define MATH2D_H

// Define PI Constant
#define PI 3.14159265


// BASIC
	float min(float,float);														// Get Max of 2 Floats
	float max(float,float);														// Get Min of 2 Floats
	float sqr(float);															// Square #
	float sign(float);															// Get Sign of Float
	float contain(float, float, float);											// Contain # in Range

// RANDOM
	float rnd();																// Get Random # from 0 to 1
	float rnd(float);															// Get Random # from 0 to Cap
	float rnd(float,float);														// Get Random # in Range
	unsigned long getTime();													// Get Current Time in Nanoseconds

// GEOMETRIC
	float calcPtDis(float, float, float, float);								// Calculate 2D Distance Btwn 2 Points
	float calcLineDis(float, float, float, float, float, float);				// Calculate 2D Distance to Line
	float calcLinePt(float, float, float, float, float, float, float, float);	// Calculate Nearest Point on Line

// TRIG
	float calcLenX(float, float);												// Calculate X Distance along Direction
	float calcLenY(float, float);												// Calculate Y Distance along Direction
	float calcPtDir(float, float, float, float);								// Calculate 2D Direction Btwn 2 Points
	float calcLineDir(float, float, float, float, float, float);				// Calculate 2D Direction to Line
	float mod(float, float);													// Modulus Function for 2 Floats

// Angle
	float calcTurnToDir(float, float);											// Calculate # to Smoothly Rotate to Angle
	float calcAngleDiff(float, float);											// Calculate Difference Btwn 2 Angles

#endif
