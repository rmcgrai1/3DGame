// Math3D.cpp
// Ryan McGrail


#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include "Math2D.h"
#include "Math3D.h"
using namespace std::chrono;

// GEOMETRIC
	// Calculate 3D Point Distance
	float calcPtDis(float x1, float y1, float z1, float x2, float y2, float z2) {
		return sqrt(sqr(x2-x1) + sqr(y2-y1) + sqr(z2-z1));
	}

