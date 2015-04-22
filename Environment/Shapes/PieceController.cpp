// PieceController.cpp

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "PieceController.h"
#include <stdlib.h>
#include "PieceGroup.h"

PieceController::PieceController() : Updateable() {
	Textures = new TexturePack;
	//Removed until fixed because of incorrect translations and rotations
	//AllPieceGroups.push_back(new PieceGroup(1200,1000,270,"Structures/SmallHut",Textures));
}

void PieceController::update(GraphicsOGL* gl, float deltaTime) {
	
}

void PieceController::newPieceGroup(float x,float y,float z,string location,string filename) {
	newPieceGroup(x,y,z,0,0,0,1,1,1,location,filename);
}

void PieceController::newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,string location,string filename) {
	newPieceGroup(x,y,z,xRot,yRot,zRot,1,1,1,location,filename);
}

void PieceController::newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,float xScale,float yScale,float zScale,string location,string filename) {
	AllPieceGroups.push_back(new PieceGroup(x,y,z,xRot,yRot,zRot,xScale,yScale,zScale,location,filename,Textures));
}

void PieceController::newPieceGroup(float x,float y,float z,string location) {
	newPieceGroup(x,y,z,0,0,0,1,1,1,location);
}

void PieceController::newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,string location) {
	newPieceGroup(x,y,z,xRot,yRot,zRot,1,1,1,location);
}

void PieceController::newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,float xScale,float yScale,float zScale,string location) {
	AllPieceGroups.push_back(new PieceGroup(x,y,z,xRot,yRot,zRot,xScale,yScale,zScale,location,Textures));
}