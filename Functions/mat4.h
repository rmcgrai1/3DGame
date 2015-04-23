// mat4.h
// Ryan McGrail

#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"

class vec4;
class mat4 {
	public:
		mat4();										// Constructors
		mat4(float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float);
		
		void getArray(float[16]);					// Get Values in 1D Array
		void setIdentity();							// Set Matrix to Identity
		float determinant();						// Calculate Determinant
		
		mat4 transpose();							// Get Transpose of Matrix
		mat4 inverse();								// Get Inverse of Matrix
		
		const mat4& operator=(const mat4&);			// Operator = to Set to Another Matrix
		mat4& operator*=(const mat4&);				// Operator *= to Multiply by Matrix
		mat4& operator*=(const float);				// Operator *= to Multiply by Float
		vec4 operator*(const vec4&);				// Operator * to Multiply by Vector
		mat4 operator*(const mat4&);				// Operator * to Multiply by Matrix
		mat4 operator!();							// Operator ! to Get Inverse
		
		float array[4][4];							// 4x4 Array of Values
};

#endif
