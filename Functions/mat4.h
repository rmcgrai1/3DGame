// mat4.h

#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"

class vec4;
class mat4 {
	public:
		mat4();
		mat4(float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float);
		void getArray(float[16]);
		void setIdentity();
		float determinant();
		
		mat4 transpose();
		mat4 inverse();
		
		const mat4& operator=(const mat4&);
		mat4& operator*=(const mat4&);
		mat4& operator*=(const float);
		vec4 operator*(const vec4&);
		mat4 operator*(const mat4&);
		mat4 operator!();
		float array[4][4];
};

#endif
