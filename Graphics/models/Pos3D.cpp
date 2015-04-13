#include<iostream>
#include <iomanip>
#include <cctype>

#include "Pos3D.h"
using namespace std;
Pos3D::Pos3D(double newX, double newY, double newZ) {
	x = newX;
	y = newY;
	z = newZ;
}

Pos3D::Pos3D(string CoordList) {
	int i;
	string Remaining = CoordList;
	string ThisNumStr;
	for(i=0;i<3;i++) {
		int pos = Remaining.find(" ");
		if(pos<0) {
			ThisNumStr = Remaining;
			Remaining = "";
		} else {
			ThisNumStr = Remaining.substr(0,pos);
			Remaining = Remaining.substr(pos+1,256);
		}
		double ThisValue = strToDouble(ThisNumStr);
		switch(i) {
			case 0:
				x = ThisValue;
			case 1:
				y = ThisValue;
			case 2:
				z = ThisValue;
		}
	}
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

double Pos3D::strToDouble(string NumberStr) {
	double Total = 0.0;
	int i=0;
	int negative = 0;
	int decimal = 0;
	int length = NumberStr.size();
	if(NumberStr.at(0)=='-') {
		negative = 1;
		i++;
	}
	while(i<length) {
		char ThisChar = NumberStr.at(i);
		if(ThisChar=='.') {
			if(decimal) {
				cout << "Unexpected second \".\" in number!!! Ignoring character!\n";
			} else {
				decimal = 1;
			}
		} else if(isdigit(ThisChar)) {
			int ThisVal = ThisChar - '0';
			if(decimal) {
				double AddNeeded = ThisVal;
				int j;
				for(j=0;j<decimal;j++) {
					AddNeeded*=0.1;
				}
				Total+=AddNeeded;
				decimal++;
			} else {
				Total*=10;
				Total+=ThisVal;
			}
		} else {
			cout << "Unexpected \"" << ThisChar << "\" in number!!! Ignoring character!!!\n";
		}
		i++;
	}
	Total*=((negative)?(-1):(1));
	return Total;
}

ostream& operator<<(ostream& output, const Pos3D pos) {
	output << "(" << pos.x << "," << pos.y << "," << pos.z << ")";
	return output;
}