// Piece.cpp

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

int Piece :: P_WALL = 1;
int Piece :: P_ELLIPSOID = 2;
int Piece :: P_BLOCK = 3;
int Piece :: P_FRUSTEM = 4;
int Piece :: P_GROUP = 5;
vector<Piece*> Piece :: pieceList;


Piece :: Piece(int newType) : Environmental(0,0,0) {
	isInstance = false;
	type = newType;
	doUpdates = false;
	visible = false;
}

Piece :: Piece(int newType, float nW1, float nW2, float nH) : Environmental(0,0,0){
	isInstance = false;
	w = nW1;
	h = nH;
	type = newType;
	doUpdates = false;
	visible = false;
}

Piece :: Piece(bool isReal, float nX, float nY, float nZ) : Environmental(nX,nY,nZ) {

	isInstance = isReal;
	doUpdates = isReal;
	visible = isReal;
}

Piece :: ~Piece() {

	//if(type == P_GROUP)
}

bool Piece :: checkOnScreen(GraphicsOGL* gl) {
	return true;
}

// INHERITED
	void Piece :: update(GraphicsOGL* gl, float deltaTime) {
		isOnScreen = true;
	}

	void Piece :: draw(GraphicsOGL* gl, float deltaTime) {
		mat4 mat;
		draw(gl, deltaTime, mat);
	}

	void Piece :: draw(GraphicsOGL* gl, float deltaTime, mat4 modMat) {
		
		modMat *= modelMat;

		gl->transformClear();		
		gl->enableShader("Piece");

		gl->setColor(255,255,255,255);

		mat4 useMat = modMat.transpose();
		gl->setShaderMat4("modelMatrix", useMat);

		if(type == P_WALL)
			gl->draw3DWall(-w/2,0,h/2,w/2,0,-h/2);
		else if(type == P_GROUP) {
			for(int i = 0; i < subpieces.size(); i++)
				subpieces[i]->draw(gl, deltaTime, modMat);
		}

		gl->disableShaders();
		gl->transformClear();
	}

	void Piece :: damage(float damage) {
	}

void Piece :: transformTranslation(float x, float y, float z) {

	mat4 rot(1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);

	modelMat *= rot;
}
void Piece :: transformScale(float s) {
	transformScale(s, s, s);
}
void Piece :: transformScale(float xS, float yS, float zS) {
	mat4 rot(xS, 0, 0, 0,
		0, yS, 0, 0,
		0, 0, zS, 0,
		0, 0, 0, 1);

	modelMat *= rot;
}
void Piece :: transformRotationX(float angle) {
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(1, 0, 0, 0,
		0, co, -si, 0,
		0, si, co, 0,
		0, 0, 0, 1);

	modelMat *= rot;
}
void Piece :: transformRotationY(float angle) {
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(co, 0, si, 0,
		0, 1, 0, 0,
		-si, 0, co, 0,
		0, 0, 0, 1);

	modelMat *= rot;
}
void Piece :: transformRotationZ(float angle) {
	angle *= -1./180*3.14159;
	float co = cos(angle), si = sin(angle);

	mat4 rot(co, -si, 0, 0,
		si, co, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	modelMat *= rot;
}

Piece* Piece :: clone() {
	Piece* p = instantiate(isInstance);

	return p;
}

Piece* Piece :: instantiate() {
	return instantiate(true);
}

Piece* Piece :: instantiate(bool top) {
	Piece* p = new Piece(top,0,0,0);
	p->type = type;
	p->w = w;
	p->h = h;
	p->modelMat = modelMat;

	if(type == P_GROUP)
		for(int i = 0; i < subpieces.size(); i++)
			p->addPiece(subpieces[i]->instantiate(false));

	if(top)
		pieceList.push_back(p);

	return p;
}

Piece* Piece :: addPiece(Piece* piece) {

	if(type != P_GROUP)
		return NULL;

	piece->isInstance = piece->visible = piece->doUpdates = isInstance;
	subpieces.push_back(piece);

	return piece;
}

Piece* Piece :: addPiece(Piece* piece, float nX, float nY, float nZ) {

	if(type != P_GROUP)
		return NULL;

	piece = piece->clone();

	addPiece(piece);
	piece->transformTranslation(nX,nY,nZ);

	return piece;
}

Piece* Piece :: addPiece(Piece* piece, float nX, float nY, float nZ, float nXR, float nYR, float nZR) {

	if(type != P_GROUP)
		return NULL;

	piece = piece->clone();

	addPiece(piece);
	piece->transformRotationZ(nZR);
	piece->transformRotationY(nYR);
	piece->transformRotationX(nXR);
	piece->transformTranslation(nX,nY,nZ);

	return piece;
}

Piece* Piece :: add3DWall(float x1, float y1, float z1, float x2, float y2, float z2) {

	if(type != P_GROUP)
		return NULL;

	Piece* newWall = new Piece(P_WALL);

	float nX, nY, nZ, nW, nH, nZD;
	nX = (x1+x2)/2;
	nY = (y1+y2)/2;
	nZ = (z1+z2)/2;
	nW = calcPtDis(x1,y1,x2,y2);
	nH = abs(z2-z1);
	nZD = calcPtDir(x1,y1,x2,y2);

	newWall->w = nW;
	newWall->h = nH;

	newWall->transformTranslation(nX,nY,nZ);
	newWall->transformRotationZ(nZD);

	return addPiece(newWall);
}

Piece* Piece :: add3DFloor(float x1, float y1, float x2, float y2, float z) {

	if(type != P_GROUP)
		return NULL;

	Piece* newFloor = new Piece(P_WALL);

	float nX, nY, nZ, nW, nH;
	nX = (x1+x2)/2;
	nY = (y1+y2)/2;
	nZ = z;
	nW = abs(x2-x1);
	nH = abs(y2-y1);

	newFloor->w = nW;
	newFloor->h = nH;

	newFloor->transformTranslation(nX,nY,nZ);
	newFloor->transformRotationX(-90);

	return addPiece(newFloor);
}

Piece* Piece :: add3DBlock(float x1, float y1, float z1, float x2, float y2, float z2) {
	add3DFloor(x2,y1,x1,y2,z1);
	add3DWall(x1,y2,z2,x1,y1,z1);
	add3DWall(x2,y1,z2,x2,y2,z1);
	add3DWall(x2,y1,z2,x1,y1,z1);
	add3DWall(x1,y2,z2,x2,y2,z1);
	add3DFloor(x1,y1,x2,y2,z2);
}


bool Piece :: collide(Physical* ch) {
	mat4 mat;

	return collide(ch, mat);
}

bool Piece :: collide(Physical* ch, mat4 modMat) {

	modMat *= modelMat;


	float chX, chY, chZ, chXP, chYP, chZP;
	float r = 7;

	vec4 fNorm(0,1,0,0);
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
		float safety = 1;

		if(type == P_WALL) {
		
			float x0, y0, z0;
			x0 = contain(-w/2, x, w/2);
			y0 = 0;
			z0 = contain(-h/2, z, h/2);

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

			float diff;
			diff = r-dis;


			if(dis <= r) { // && (chZ+r >= -h/2 && chZ-r <= h/2)) {
				isGround = (fNorm[2] > .5);
				
				chX += normX*diff;
				chY += normY*diff;
				chZ += normZ*diff;

				didCollide = true;
			}
		}
		else if(type == P_GROUP) {
			for(int i = 0; i < subpieces.size(); i++) 
				didCollide = (didCollide || subpieces[i]->collide(ch, modMat));
		}

	if(type != P_GROUP) {
		// Transform Point to Real Space
		chVec[0] = chX;
		chVec[1] = chY;
		chVec[2] = chZ;

		chVec = modMat * chVec;

		ch->setX(chVec[0]);
		ch->setY(chVec[1]);
		ch->setZ(chVec[2]-r);

		if(didCollide && isGround)
			ch->placeOnGround();
	}

	return didCollide;
}

float Piece :: calcFloorZ() {
	return 0;
}
