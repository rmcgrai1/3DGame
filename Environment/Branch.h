// Branch.h
// Ryan McGrail

#ifndef BRANCH_H
#define BRANCH_H

#include "../Graphics/GraphicsOGL.h"
#include <vector>

class Branch {
	public:
		Branch(int,int,float,float,float);						// Constructor
		void draw(GraphicsOGL*, float,float,float);				// Drawing

	private:
		vector<Branch*> subbranches;							// Vector of Subbranches

		int numBranches;										// Number of Subbranches
		float len;												// Length of Branch
		float dir;												// XY Direction of Branch
		float zDir;												// Z Direction of Branch
};

#endif
