#ifndef FACE_H
#define FACE_H

#include<iostream>
#include <iomanip>
#include "Pos3D.h"
#include "Mtl.h"

using namespace std;
class Face {
	friend ostream& operator<<(ostream&, const Face);
	public:
		Face(int newV1=1,int newVT1=1,int newVN1=1, int newV2=1,int newVT2=1,int newVN2=1, int newV3=1,int newVT3=1,int newVN3=1, Mtl *MaterialToUse=new Mtl);
		void setPoint1(int newV,int newVT,int newVN);
		void setPoint2(int newV,int newVT,int newVN);
		void setPoint3(int newV,int newVT,int newVN);
		void setVertex(int value1,int value2,int value3);
		void setTexCoord(int value1,int value2,int value3);
		void setVNormal(int value1,int value2,int value3);
		void setMaterial(Mtl *MaterialToUse);
		Mtl *getMaterial();
		Pos3D *getVertex(Pos3D ** Vertices, int VertexCount, int PointNo);
		Pos3D *getTexCoord(Pos3D ** TexCoords, int TexCoordCount, int PointNo);
		Pos3D *getVNormal(Pos3D ** VNormal, int VNormalCount, int PointNo);
	private:
		int V[3];
		int VT[3];
		int VN[3];
		Mtl *Material;
};

#endif