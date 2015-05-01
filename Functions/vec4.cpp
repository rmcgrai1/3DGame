// vec4.cpp
// Ryan McGrail

#include <iostream>
#include "vec4.h"
#include "mat4.h"
using namespace std;

// Constructor
vec4 :: vec4(float nA1, float nA2, float nA3, float nA4) {

	// Set Values in Array
	array[0] = nA1; array[1] = nA2; array[2] = nA3; array[3] = nA4;
}

// Operator =, Setting Equal to Vector
const vec4& vec4 :: operator=(const vec4& other) {

	// Copy Elements into Array
	for(int i = 0; i < 4; i++)
		array[i] = other.array[i];

	// Return Self
	return *this;
}

// Operator [], Random Access
float& vec4 :: operator[](const int index) {
	return array[index];
}

// Operator *=, Multiplying by Matrix	
vec4& vec4 :: operator*=(const mat4& other) {

	// Multiply by Matrix
	float v;
	for(int c = 0; c < 4; c++) {
		v = 0;
		for(int i = 0; i < 4; i++)
			v += array[c]*other.array[i][c];
		array[c] = v;
	}

	// Return Self
	return *this;
}
