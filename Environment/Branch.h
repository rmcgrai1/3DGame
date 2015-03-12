// Branch.h


#ifndef BRANCH_H
#define BRANCH_H

#include "../Graphics/GraphicsOGL.h"
#include <vector>

class Branch {
	public:
		Branch(int,int,float,float,float);
		void draw(GraphicsOGL*, float,float,float);

	private:
		vector<Branch*> subbranches;

		int numBranches;
		float len;
		float dir;
		float zDir;
};

#endif
