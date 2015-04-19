#include<iostream>
#include <iomanip>
#include "Pos3D.h"
#include "Mtl.h"

#include "Face.h"
using namespace std;
Face::Face(int newV1,int newVT1,int newVN1, int newV2,int newVT2,int newVN2, int newV3,int newVT3,int newVN3, Mtl *MaterialToUse) {
	V[0] = newV1 - 1;
	VT[0] = newVT1 - 1;
	VN[0] = newVN1 - 1;
	V[1] = newV2 - 1;
	VT[1] = newVT2 - 1;
	VN[1] = newVN2 - 1;
	V[2] = newV3 - 1;
	VT[2] = newVT3 - 1;
	VN[2] = newVN3 - 1;
	
	Material = MaterialToUse;
}

Face::Face(string CornersList, Mtl *MaterialToUse) {
	int i;
	string Remaining = CornersList;
	string ThisSubStr;
	for(i=0;i<3;i++) {
		int pos = Remaining.find(" ");
		if(pos<0) {
			ThisSubStr = Remaining;
			Remaining = "";
		} else {
			ThisSubStr = Remaining.substr(0,pos);
			Remaining = Remaining.substr(pos+1,256);
		}
		setPointStr(ThisSubStr,i);
	}
	
	Material = MaterialToUse;
}

void Face::setPointStr(string PointStr, int PointNo) {
	if(PointNo<0 || PointNo>=3) {
		cout << "WARNING: Tried setting point " << PointNo << " of face out of bounds! - Moving in bounds!\n";
		PointNo = PointNo%3;
	}
	int i;
	string Remaining = PointStr;
	string ThisSubStr;
	for(i=0;i<3;i++) {
		int pos = Remaining.find("/");
		if(pos<0) {
			ThisSubStr = Remaining;
			Remaining = "";
		} else {
			ThisSubStr = Remaining.substr(0,pos);
			Remaining = Remaining.substr(pos+1,256);
		}
		int j, Total=0;
		for(j=0;j<ThisSubStr.size();j++) {
			char ThisChar = ThisSubStr.at(j);
			if(isdigit(ThisChar)) {
				Total*=10;
				Total+=(ThisChar - '0');
			} else {
				cout << "Unrecognized character \"" << ThisChar << "\" in number!!! Ignoring character!!!\n";
			}
		}
		switch(i) {
			case 0:
				V[PointNo] = Total - 1;
			case 1:
				VT[PointNo] = Total - 1;
			case 2:
				VN[PointNo] = Total - 1;
		}
	}
}

void Face::setPoint1(int newV,int newVT,int newVN) {
	V[0] = newV - 1;
	VT[0] = newVT - 1;
	VN[0] = newVN - 1;
}

void Face::setPoint2(int newV,int newVT,int newVN) {
	V[1] = newV - 1;
	VT[1] = newVT - 1;
	VN[1] = newVN - 1;
}

void Face::setPoint3(int newV,int newVT,int newVN) {
	V[2] = newV - 1;
	VT[2] = newVT - 1;
	VN[2] = newVN - 1;
}

void Face::setVertex(int value1,int value2,int value3) {
	V[0] = value1 - 1;
	V[1] = value2 - 1;
	V[2] = value3 - 1;
}

void Face::setTexCoord(int value1,int value2,int value3) {
	VT[0] = value1 - 1;
	VT[1] = value2 - 1;
	VT[2] = value3 - 1;
}

void Face::setVNormal(int value1,int value2,int value3) {
	VN[0] = value1 - 1;
	VN[1] = value2 - 1;
	VN[2] = value3 - 1;
}

Pos3D *Face::getVertex(Pos3D ** Vertices, int VertexCount, int PointNo) {
	int i = V[PointNo];
	if(i<VertexCount && i>=0) {
		return Vertices[i];
	} else {
		return Vertices[0];
	}
}

Pos3D *Face::getTexCoord(Pos3D ** TexCoords, int TexCoordCount, int PointNo) {
	int i = VT[PointNo];
	if(i<TexCoordCount && i>=0) {
		return TexCoords[i];
	} else {
		return TexCoords[0];
	}
}

Pos3D *Face::getVNormal(Pos3D ** VNormal, int VNormalCount, int PointNo) {
	int i = VN[PointNo];
	if(i<VNormalCount && i>=0) {
		return VNormal[i];
	} else {
		return VNormal[0];
	}
}

void Face::setMaterial(Mtl *MaterialToUse) {
	Material = MaterialToUse;
}

Mtl *Face::getMaterial() {
	return Material;
}

ostream& operator<<(ostream& output, const Face face) {
	int i;
	for(i=0;i<3;i++) {
		output << face.V[i]+1 << "/" << face.VT[i]+1 << "/" << face.VN[i]+1;
		if(i<2) {
			output << " ";
		}
	}
	return output;
}