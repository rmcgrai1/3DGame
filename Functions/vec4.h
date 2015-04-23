// vec4.h
// Ryan McGrail

#ifndef VEC4_H
#define VEC4_H

#include "mat4.h"

class mat4;
class vec4 {
	public:
		vec4(float,float,float,float);				// Constructor
		
		const vec4& operator=(const vec4&);			// Operator =, Setting Equal to Another Vector
		vec4& operator*=(const mat4&);				// Operator *=, Multiplying by Matrix
		float& operator[](const int index);			// Operator[], Random Access
		float array[4];								// Array of Values
};

#endif
