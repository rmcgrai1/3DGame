// Piece.cpp
// Ryan McGrail

#include <iostream>
#include "Piece.h"
#include "../../Primitives/Physical.h"
#include "../../Functions/mat4.h"
#include "../../Functions/vec4.h"
#include "../../Functions/Math2D.h"
#include "../../Functions/Math3D.h"
#include <cmath>
#include <vector>
using namespace std;

// Initialize Types of Pieces
int Piece :: P_WALL = 1;
int Piece :: P_GROUP = 5;
vector<Piece*> Piece :: pieceList;

// Constructor, Blueprint
Piece :: Piece(int newType) : Environmental(0,0,0) {
	isInstance = false;
	type = newType;
	doUpdates = false;
	visible = false;
}

// Constructor, Blueprint
Piece :: Piece(int newType, float nW1, float nW2, float nH) : Environmental(0,0,0){
	isInstance = false;
	w = nW1;
	h = nH;
	type = newType;
	doUpdates = false;
	visible = false;
}

// Constructor, Real
Piece :: Piece(bool isReal, float nX, float nY, float nZ) : Environmental(nX,nY,nZ) {

	isInstance = isReal;
	doUpdates = isReal;
	visible = isReal;
}

// Deconstructor
Piece :: ~Piece() {
}

// Checking if Onscreens
bool Piece :: checkOnScreen(GraphicsOGL* gl) {
	return true;
}

// INHERITED
	// Updating
	void Piece :: update(GraphicsOGL* gl, float deltaTime) {
		isOnScreen = true;
	}

	// Drawing Piece (Top Level)
	void Piece :: draw(GraphicsOGL* gl, float deltaTime) {
		mat4 mat;
		draw(gl, deltaTime, mat);
	}

	// Drawing Piece (Lower-Level)
	void Piece :: draw(GraphicsOGL* gl, float deltaTime, mat4 modMat) {
		
		// Apply Parent Model Matrix to Model Matrix
		modMat *= modelMat;

		// Clear Transformations, Enable Piece Shader
		gl->transformClear();		
		gl->enableShader("Piece");

		// Set Color to White
		gl->setColor(255,255,255,255);

		// Use Transpose of Model Matrix for Drawing
		mat4 useMat = modMat.transpose();
		gl->setShaderMat4("modelMatrix", useMat);

		// Drawing Wall
		if(type == P_WALL)
			gl->draw3DWall(-w/2,0,h/2,w/2,0,-h/2);
		// Drawing Group
		else if(type == P_GROUP) {
			for(int i = 0; i < subpieces.size(); i++)
				subpieces[i]->draw(gl, deltaTime, modMat);
		}

		// Disabling Shader, Clearing Transformation
		gl->disableShaders();
		gl->transformClear();
	}

// Damaging Piece
void Piece :: damage(float damage) {
}

// Transforming Translation
void Piece :: transformTranslation(float x, float y, float z) {

	// Create Translation Matrix
	mat4 rot(1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);

	// Apply Translation Matrix to Model Matrix
	modelMat *= rot;
}
// Transforming Scale Uniformly
void Piece :: transformScale(float s) {
	transformScale(s, s, s);
}
// Transforming Scale Nonuniformly
void Piece :: transformScale(float xS, float yS, float zS) {
	// Create Scale Matrix
	mat4 rot(xS, 0, 0, 0,
		0, yS, 0, 0,
		0, 0, zS, 0,
		0, 0, 0, 1);

	// Apply Scale Matrix to Model Matrix
	modelMat *= rot;
}
// Transforming Rotation Along X Axis
void Piece :: transformRotationX(float angle) {

	// Generate Rotation Matrix
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(1, 0, 0, 0,
		0, co, -si, 0,
		0, si, co, 0,
		0, 0, 0, 1);

	// Apply Rotation Matrix to Model Matrix
	modelMat *= rot;
}
// Transforming Rotation Along Y Axis
void Piece :: transformRotationY(float angle) {

	// Generate Rotation Matrix
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(co, 0, si, 0,
		0, 1, 0, 0,
		-si, 0, co, 0,
		0, 0, 0, 1);

	// Apply Rotation Matrix to Model Matrix
	modelMat *= rot;
}
// Transforming Rotation Along Z Axis
void Piece :: transformRotationZ(float angle) {

	// Generate Rotation Matrix
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(co, -si, 0, 0,
		si, co, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	// Apply Rotation Matrix to Model Matrix
	modelMat *= rot;
}

// Clone Piece
Piece* Piece :: clone() {
	Piece* p = instantiate(isInstance);

	return p;
}

// Instantiate Top-Level Object
Piece* Piece :: instantiate() {
	return instantiate(true);
}

// Generic Instantiation
Piece* Piece :: instantiate(bool top) {

	// Create New Piece, Copy Vars to It
	Piece* p = new Piece(top,0,0,0);
	p->type = type;
	p->w = w;
	p->h = h;
	p->modelMat = modelMat;

	// Add Subpieces
	if(type == P_GROUP)
		for(int i = 0; i < subpieces.size(); i++)
			p->addPiece(subpieces[i]->instantiate(false));

	// If Top-Level, Add to List of Instantiated Objects
	if(top)
		pieceList.push_back(p);

	return p;
}

// Add Piece Object to Group
Piece* Piece :: addPiece(Piece* piece) {

	// Only Allow if Group!!
	if(type != P_GROUP)
		return NULL;

	// Set Vars
	piece->isInstance = piece->visible = piece->doUpdates = isInstance;
	// Add to Subpiece List
	subpieces.push_back(piece);

	return piece;
}

// Adding Clone of Piece Object to Group
Piece* Piece :: addPiece(Piece* piece, float nX, float nY, float nZ) {

	// If Not Group, STOP!
	if(type != P_GROUP)
		return NULL;

	// Create Clone
	piece = piece->clone();

	// Add Clone
	addPiece(piece);
	
	// Position
	piece->transformTranslation(nX,nY,nZ);

	return piece;
}

// Adding Clone of Piece Object to Group, Positioned & Rotated
Piece* Piece :: addPiece(Piece* piece, float nX, float nY, float nZ, float nXR, float nYR, float nZR) {

	// If Not Group, IGNORE!!
	if(type != P_GROUP)
		return NULL;

	// Clone Piece
	piece = piece->clone();

	// Add Clone
	addPiece(piece);
	
	// Position & Rotate
	piece->transformRotationZ(nZR);
	piece->transformRotationY(nYR);
	piece->transformRotationX(nXR);
	piece->transformTranslation(nX,nY,nZ);

	return piece;
}

// Adding Wall to Group
Piece* Piece :: add3DWall(float x1, float y1, float z1, float x2, float y2, float z2) {

	// If Not Group, STOP!!
	if(type != P_GROUP)
		return NULL;

	// Create New Wall
	Piece* newWall = new Piece(P_WALL);

	// Generate XYZ and XYZ Rotation
	float nX, nY, nZ, nW, nH, nZD;
	nX = (x1+x2)/2;
	nY = (y1+y2)/2;
	nZ = (z1+z2)/2;
	nW = calcPtDis(x1,y1,x2,y2);
	nH = abs(z2-z1);
	nZD = calcPtDir(x1,y1,x2,y2);

	// Set Width
	newWall->w = nW;
	newWall->h = nH;

	// Set Translation & Rotation
	newWall->transformTranslation(nX,nY,nZ);
	newWall->transformRotationZ(nZD);

	return addPiece(newWall);
}

// Adding Floor to Group
Piece* Piece :: add3DFloor(float x1, float y1, float x2, float y2, float z) {

	// If Not Group, STOP!!!
	if(type != P_GROUP)
		return NULL;

	// Create New Floor
	Piece* newFloor = new Piece(P_WALL);

	// Generate XYZ
	float nX, nY, nZ, nW, nH;
	nX = (x1+x2)/2;
	nY = (y1+y2)/2;
	nZ = z;
	nW = abs(x2-x1);
	nH = abs(y2-y1);

	// Set Width
	newFloor->w = nW;
	newFloor->h = nH;

	// Position and Rotate
	newFloor->transformTranslation(nX,nY,nZ);
	newFloor->transformRotationX(-90);

	return addPiece(newFloor);
}

// Add Block to Group
Piece* Piece :: add3DBlock(float x1, float y1, float z1, float x2, float y2, float z2) {
	
	// Add Floor, Walls, and Floor
	add3DFloor(x2,y1,x1,y2,z1);
	add3DWall(x1,y2,z2,x1,y1,z1);
	add3DWall(x2,y1,z2,x2,y2,z1);
	add3DWall(x2,y1,z2,x1,y1,z1);
	add3DWall(x1,y2,z2,x2,y2,z1);
	add3DFloor(x1,y1,x2,y2,z2);
}

// Collide Character w/ Model, Top Level
bool Piece :: collide(Physical* ch) {
	mat4 mat;

	return collide(ch, mat);
}

// Collide Character w/ Model, Lower Level
bool Piece :: collide(Physical* ch, mat4 modMat) {

	// Apply Upper Levels' Model Matrices to Model Matrix
	modMat *= modelMat;

	float chX, chY, chZ, chXP, chYP, chZP;
	float r = 7;

	float nY = 1;
	vec4 fNorm(0,nY,0,0);
	
	// Position and Previous Position Vector
	vec4 chVec(ch->getX(), ch->getY(), ch->getZ()+r, 1);
	vec4 chVecP(ch->getXPrev(), ch->getYPrev(), ch->getZPrev()+r, 1);

	bool isGround = false, didCollide = false;

	// Transform Point to Model Space
		chVec = !modMat * chVec;
		chVecP = !modMat * chVecP;
		fNorm = modMat * fNorm;

		chX = chVec[0];
		chY = chVec[1];
		chZ = chVec[2];
		chXP = chVecP[0];
		chYP = chVecP[1];
		chZP = chVecP[2];

	// Collide
		float safety = 3;

		if(type == P_WALL) {
			// CALCULATE DISTANCES FROM WALL FOR MOVING
				float x0, y0, z0;
				x0 = contain(-w/2, chX, w/2);
				y0 = 0;
				z0 = contain(-h/2, chZ, h/2);

				float dis;
				dis = calcPtDis(x0,y0,z0,chX,chY,chZ);
				
				float xyDis = calcLineDis(chX,chY,-w/2,0,w/2,0);
				float yzDis = calcLineDis(chY,chZ,0,h/2,0,-h/2);
				float xyDir = calcLineDir(chX,chY,-w/2,0,w/2,0);
				float yzDir = calcLineDir(chY,chZ,0,h/2,0,-h/2);

				float coXY, siXY, coYZ, siYZ;
				coXY = calcLenX(1,xyDir);
				siXY = calcLenY(1,xyDir);
				coYZ = calcLenX(1,yzDir);
				siYZ = calcLenY(1,yzDir);

				float normX, normY, normZ;
				normX = abs(coYZ)*coXY;
				normY = abs(coYZ)*siXY;
				normZ = siYZ;
					
				isGround = (abs(fNorm[2]) > .5);

				float eDis = 0;
				eDis = calcPtDis(x0,z0,chX,chZ);
				safety = 1;

			// Calculate Distance Needed to Move Out of Wall
			float diff;
			diff = r-dis;

			// If Wall/Slope
			if(!isGround) {
				// Move Character Out of Wall if Too Close
				if(dis <= r) {
					chX += normX*diff;
					chY += normY*diff;
					chZ += normZ*diff;
					
					didCollide = true;
				}
			} 
			// Otherwise, If Floor,
			else {
				// If Character In Floor, Push Out
				if(dis <= r && eDis <= r) {
					if(eDis == 0)
						chY = r;
					else {
						chX += normX*diff;
						chY += normY*diff;
						chZ += normZ*diff;
					}
					didCollide = true;
				}
			}
		}
		// If Group, Collide w/ Subpieces
		else if(type == P_GROUP)
			for(int i = 0; i < subpieces.size(); i++) 
				didCollide = (didCollide || subpieces[i]->collide(ch, modMat));

	if(type != P_GROUP) {
		// Get Character Position as Float Array
		chVec[0] = chX;
		chVec[1] = chY;
		chVec[2] = chZ;

		// Transform Character Position Back to Model Space
		chVec = modMat * chVec;

		// Set Character Position
		ch->setX(chVec[0]);
		ch->setY(chVec[1]);
		ch->setZ(chVec[2]-r);

		// If Collided w/ Ground, Stop Z Movement and Assume this is Ground
		if(didCollide && isGround) {
			ch->placeOnGround();
			ch->setZVelocity(0);
		}
	}

	return didCollide;
}