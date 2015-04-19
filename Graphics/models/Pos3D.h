#ifndef POS3D_H
#define POS3D_H

#include<iostream>
#include <iomanip>

using namespace std;
class Pos3D {
	friend ostream& operator<<(ostream&, const Pos3D);
	public:
		Pos3D(double newX = 0, double newY = 0, double newZ = 0);
		Pos3D(string CoordList);
		void setPos(double newX, double newY, double newZ);
		void setX(double value);
		void setY(double value);
		void setZ(double value);
		double getX();
		double getY();
		double getZ();
	private:
		double strToDouble(string NumberStr);
		
		double x;
		double y;
		double z;
};

#endif