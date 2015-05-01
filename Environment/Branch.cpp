// Branch.cpp
// Ryan McGrail

#include "../Functions/Math2D.h"
#include <stdlib.h>
#include "../Graphics/GraphicsOGL.h"
#include <vector>
#include <cmath>
#include "Branch.h"
#include <iostream>
using namespace std;


// Constructor
Branch :: Branch(int rec, int numB, float l, float d, float zD) {
	rec++;
	numBranches = numB;
	len = l;
	dir = d;
	zDir = zD;

	// If 10 Levels of Recursion, STOP
	if(rec == 10)
		numBranches = 0;

	// Recursively Add Branches
	for(int i = 0; i < numBranches; i++) {
		int bNB;
		if(len > 2)
			bNB = 10-rec;//1 + rand()%6;
		else
			bNB = 0;
		float bL, bD, bZD, f;
		f = 16/(16-len);


		// Determine New Branch Length, Branch Direction, Branch ZDirection
		bL = (.3 + ((rand() % 100)/100.)*.3)*l;
		bD = d + (((rand() % 100)/100.)-.5)*60*f;
		bZD = zD + (((rand() % 100)/100.)-.5)*60*f;

		// Add Branch
		subbranches.push_back(new Branch(rec,bNB, bL, bD, bZD));
	}
}

// Draw Branches as 3D Lines
void Branch :: draw(GraphicsOGL* gl, float x, float y, float z) {

	float x2, y2, z2;

	x2 = x + calcLenX(calcLenX(len,dir),zDir);
	y2 = y - calcLenX(calcLenY(len,dir),zDir);
	z2 = z + calcLenY(len, zDir);

	gl->draw3DLine(x,y,z,x2,y2,z2);

	for(int i = 0; i < numBranches; i++)
		subbranches[i]->draw(gl,x2,y2,z2);
}
