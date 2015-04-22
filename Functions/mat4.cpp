// mat4.cpp


#include <iostream>
#include "mat4.h"
using namespace std;

mat4 :: mat4() {
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			array[r][c] = (r == c);
}

mat4 :: mat4(float nA1, float nA2, float nA3, float nA4, float nB1, float nB2, float nB3, float nB4, float nC1, float nC2, float nC3, float nC4, float nD1, float nD2, float nD3, float nD4) {
	array[0][0] = nA1;
	array[0][1] = nA2;
	array[0][2] = nA3;
	array[0][3] = nA4;

	array[1][0] = nB1;
	array[1][1] = nB2;
	array[1][2] = nB3;
	array[1][3] = nB4;

	array[2][0] = nC1;
	array[2][1] = nC2;
	array[2][2] = nC3;
	array[2][3] = nC4;

	array[3][0] = nD1;
	array[3][1] = nD2;
	array[3][2] = nD3;
	array[3][3] = nD4;
}

float mat4 :: determinant() {
	float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
	m00 = array[0][0];
	m01 = array[0][1];
	m02 = array[0][2];
	m03 = array[0][3];
	m10 = array[1][0];
	m11 = array[1][1];
	m12 = array[1][2];
	m13 = array[1][3];
	m20 = array[2][0];
	m21 = array[2][1];
	m22 = array[2][2];
	m23 = array[2][3];
	m30 = array[3][0];
	m31 = array[3][1];
	m32 = array[3][2];
	m33 = array[3][3];

	return m03*m12*m21*m30 - m02*m13*m21*m30 - m03*m11*m22*m30 + m01*m13*m22*m30+
   m02*m11*m23*m30 - m01*m12*m23*m30 - m03*m12*m20*m31 + m02*m13*m20*m31+
   m03*m10*m22*m31 - m00*m13*m22*m31 - m02*m10*m23*m31 + m00*m12*m23*m31+
   m03*m11*m20*m32 - m01*m13*m20*m32 - m03*m10*m21*m32 + m00*m13*m21*m32+
   m01*m10*m23*m32 - m00*m11*m23*m32 - m02*m11*m20*m33 + m01*m12*m20*m33+
   m02*m10*m21*m33 - m00*m12*m21*m33 - m01*m10*m22*m33 + m00*m11*m22*m33;
}

mat4 mat4 :: transpose() {
	mat4 trMat;

	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			trMat.array[r][c] = array[c][r];

	return trMat;
}

mat4 mat4 :: inverse() {

	float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
	m00 = array[0][0];
	m01 = array[0][1];
	m02 = array[0][2];
	m03 = array[0][3];
	m10 = array[1][0];
	m11 = array[1][1];
	m12 = array[1][2];
	m13 = array[1][3];
	m20 = array[2][0];
	m21 = array[2][1];
	m22 = array[2][2];
	m23 = array[2][3];
	m30 = array[3][0];
	m31 = array[3][1];
	m32 = array[3][2];
	m33 = array[3][3];

	float b11, b12, b13, b14, b21, b22, b23, b24, b31, b32, b33, b34, b41, b42, b43, b44;
	b11 = m12*m23*m31 - m13*m22*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 + m11*m22*m33;
	b12 = m03*m22*m31 - m02*m23*m31 - m03*m21*m32 + m01*m23*m32 + m02*m21*m33 - m01*m22*m33;
	b13 = m02*m13*m31 - m03*m12*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 + m01*m12*m33;
	b14 = m03*m12*m21 - m02*m13*m21 - m03*m11*m22 + m01*m13*m22 + m02*m11*m23 - m01*m12*m23;
	b21 = m13*m22*m30 - m12*m23*m30 - m13*m20*m32 + m10*m23*m32 + m12*m20*m33 - m10*m22*m33;
	b22 = m02*m23*m30 - m03*m22*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 + m00*m22*m33;
	b23 = m03*m12*m30 - m02*m13*m30 - m03*m10*m32 + m00*m13*m32 + m02*m10*m33 - m00*m12*m33;
	b24 = m02*m13*m20 - m03*m12*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 + m00*m12*m23;
	b31 = m11*m23*m30 - m13*m21*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 + m10*m21*m33;
	b32 = m03*m21*m30 - m01*m23*m30 - m03*m20*m31 + m00*m23*m31 + m01*m20*m33 - m00*m21*m33;
	b33 = m01*m13*m30 - m03*m11*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 + m00*m11*m33;
	b34 = m03*m11*m20 - m01*m13*m20 - m03*m10*m21 + m00*m13*m21 + m01*m10*m23 - m00*m11*m23;
	b41 = m12*m21*m30 - m11*m22*m30 - m12*m20*m31 + m10*m22*m31 + m11*m20*m32 - m10*m21*m32;
	b42 = m01*m22*m30 - m02*m21*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 + m00*m21*m32;
	b43 = m02*m11*m30 - m01*m12*m30 - m02*m10*m31 + m00*m12*m31 + m01*m10*m32 - m00*m11*m32;
	b44 = m01*m12*m20 - m02*m11*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 + m00*m11*m22;

	mat4 inv(b11,b12,b13,b14,b21,b22,b23,b24,b31,b32,b33,b34,b41,b42,b43,b44);
	inv *= 1./determinant();

	return inv;
}
	
mat4 mat4 :: operator!() {
	return inverse();
}

const mat4& mat4 :: operator=(const mat4& other) {
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			array[r][c] = other.array[r][c];

	return *this;
}
	
mat4& mat4 :: operator*=(const mat4& other) {
	float oldValues[4][4];
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			oldValues[r][c] = array[r][c];

	float v;
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++) {
			v = 0;
			for(int i = 0; i < 4; i++)
				v += oldValues[r][i]*other.array[i][c];
			array[r][c] = v;
		}

	return *this;
}

mat4 mat4 :: operator*(const mat4& other) {
	mat4 newMat = *this;

	float v;
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++) {
			v = 0;
			for(int i = 0; i < 4; i++)
				v += array[r][i]*other.array[i][c];
			newMat.array[r][c] = v;
		}

	return newMat;
}

vec4 mat4 :: operator*(const vec4& other) {
	vec4 newVec(0,0,0,0);

	float v;
	for(int r = 0; r < 4; r++) {
		v = 0;
			
		for(int c = 0; c < 4; c++)
			v += array[r][c]*other.array[c];

		newVec[r] = v;
	}

	return newVec;
}

mat4& mat4 :: operator*=(const float v) {
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			array[r][c] *= v;

	return *this;
}

void mat4 :: setIdentity() {
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			array[r][c] = (r == c);
}
	
void mat4 :: getArray(float out[16]) {
	int i = 0;
	for(int r = 0; r < 4; r++)
		for(int c = 0; c < 4; c++)
			out[i++] = array[r][c];
}
