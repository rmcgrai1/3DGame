// PieceGroup.cpp

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "PieceGroup.h"

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	JSONdirectory = location;
	JSONfilename = "model.json";
	x=new_x;
	y=new_y;
	z=new_z;
	xRot=new_xRot;
	yRot=new_yRot;
	zRot=new_zRot;
	xScale=new_xScale;
	yScale=new_yScale;
	zScale=new_zScale;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,string filename,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	JSONdirectory = location;
	JSONfilename = filename;
	x=new_x;
	y=new_y;
	z=new_z;
	xRot=new_xRot;
	yRot=new_yRot;
	zRot=new_zRot;
	xScale=new_xScale;
	yScale=new_yScale;
	zScale=new_zScale;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	JSONdirectory = location;
	JSONfilename = "model.json";
	x=new_x;
	y=new_y;
	z=new_z;
	xRot=new_xRot;
	yRot=new_yRot;
	zRot=new_zRot;
	xScale=1;
	yScale=1;
	zScale=1;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	JSONdirectory = location;
	JSONfilename = "model.json";
	x=new_x;
	y=new_y;
	z=new_z;
	xRot=0;
	yRot=0;
	zRot=0;
	xScale=1;
	yScale=1;
	zScale=1;
}

int PieceGroup::collide() {
	return 0; // temporarily return false!
}

void PieceGroup::update(GraphicsOGL* gl, float deltaTime) {
	cout << "Updating PieceGroup\n";
}

void PieceGroup::draw(GraphicsOGL* gl, float deltaTime) {
	cout << "Drawing PieceGroup\n";
}

void PieceGroup::damage(float amount) {
	
}

float PieceGroup::calcFloorZ() {
	
}

void PieceGroup::loadfromJSON() {
	
}