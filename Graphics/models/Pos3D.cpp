#include<iostream>
#include <iomanip>

#include "Pos3D.h"
using namespace std;
Pos3D::Pos3D(double newX, double newY, double newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

void Pos3D::setPos(double newX, double newY, double newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

void Pos3D::setX(double value) {
	x = value;
}

void Pos3D::setY(double value) {
	y = value;
}

void Pos3D::setZ(double value) {
	z = value;
}

double Pos3D::getX() {
	return x;
}

double Pos3D::getY() {
	return y;
}

double Pos3D::getZ() {
	return z;
}

ostream& operator<<(ostream& output, const Pos3D pos) {
	output << "(" << pos.x << "," << pos.y << "," << pos.z << ")";
	return output;
}