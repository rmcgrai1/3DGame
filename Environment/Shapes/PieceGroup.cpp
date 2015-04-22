// PieceGroup.cpp

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../Environmental.h"
#include "../../JSON/JSON.h"
#include "PieceExt.h"
#include "PieceGroup.h"

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	TPfolder = TP->GetFolder();
	directory = location;
	JSONdirectory = TPfolder + "/" + location;
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
	loadfromJSON();
	isDrawRoot = 1;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,string filename,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	TPfolder = TP->GetFolder();
	directory = location;
	JSONdirectory = TPfolder + "/" + location;
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
	loadfromJSON();
	isDrawRoot = 1;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	TPfolder = TP->GetFolder();
	directory = location;
	JSONdirectory = TPfolder + "/" + location;
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
	loadfromJSON();
	isDrawRoot = 1;
}

PieceGroup::PieceGroup(float new_x,float new_y,float new_z,string location,TexturePack *TP):Environmental(new_x,new_y) {
	Textures = TP;
	TPfolder = TP->GetFolder();
	directory = location;
	JSONdirectory = TPfolder + "/" + location;
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
	loadfromJSON();
	isDrawRoot = 1;
}

void PieceGroup::DrawHere(GraphicsOGL* gl, float deltaTime) {
	gl->transformTranslation(x,y,z);
	gl->transformScale(xScale,yScale,zScale);
	gl->transformRotationX(xRot);
	gl->transformRotationY(yRot);
	gl->transformRotationZ(zRot);
	
	vector<PieceGroup *>::iterator i;
	for(i=SubGroups.begin();i!=SubGroups.end();i++) {
		(*i)->DrawHere(gl, deltaTime);
	}
	vector<PieceExt *>::iterator j;
	for(j=Pieces.begin();j!=Pieces.end();j++) {
		(*j)->draw(gl, deltaTime);
	}
	
	gl->transformRotationZ(-1*zRot);
	gl->transformRotationY(-1*yRot);
	gl->transformRotationX(-1*xRot);
	gl->transformScale(1/xScale,1/yScale,1/zScale);
	gl->transformTranslation(-1*x,-1*y,-1*z);
}

void PieceGroup::setDrawRoot(int isRoot) {
	isDrawRoot = isRoot;
}

int PieceGroup::collide() {
	return 0; // temporarily return false!
}

void PieceGroup::update(GraphicsOGL* gl, float deltaTime) {
	vector<PieceExt *>::iterator j;
	for(j=Pieces.begin();j!=Pieces.end();j++) {
		(*j)->update(gl, deltaTime);
	}
}

void PieceGroup::draw(GraphicsOGL* gl, float deltaTime) {
	if(isDrawRoot) { // only draw if isn't created by another PieceGroup
		gl->transformClear();
		DrawHere(gl, deltaTime);
		gl->transformClear();
	}
}

void PieceGroup::damage(float amount) {
	
}

float PieceGroup::calcFloorZ() {
	
}

void PieceGroup::loadfromJSON() {
	string fullJSONpath = JSONdirectory + "/" + JSONfilename;
	JSON *GroupFile = new JSON(fullJSONpath);
	
	vector<JSON *> PieceGroupsJSON = GroupFile->getClassArray("PieceGroups");
	vector<JSON *>::iterator i;
	for(i=PieceGroupsJSON.begin();i!=PieceGroupsJSON.end();i++) {
		JSON *Dimensions = (*i)->getClass("dimensions");
		string Folder = (*i)->getString("folder");
		string Filename = (*i)->getString("filename");
		string fullfolder = directory + "/" + Folder;
		SubGroups.push_back(new PieceGroup(Dimensions->getFloat("x"),Dimensions->getFloat("y"),Dimensions->getFloat("z"),Dimensions->getFloat("xRot"),Dimensions->getFloat("yRot"),Dimensions->getFloat("zRot"),Dimensions->getFloat("xScale"),Dimensions->getFloat("yScale"),Dimensions->getFloat("zScale"),fullfolder,Filename,Textures));
		SubGroups.back()->setDrawRoot(0);
	}
	vector<JSON *> PieceExtsJSON = GroupFile->getClassArray("PieceExts");
	for(i=PieceExtsJSON.begin();i!=PieceExtsJSON.end();i++) {
		JSON *Dimensions = (*i)->getClass("dimensions");
		string Folder = (*i)->getString("folder");
		string Filename = (*i)->getString("filename");
		string fullfolder = directory + "/" + Folder;
		Pieces.push_back(new PieceExt(Dimensions->getFloat("x"),Dimensions->getFloat("y"),Dimensions->getFloat("z"),Dimensions->getFloat("xRot"),Dimensions->getFloat("yRot"),Dimensions->getFloat("zRot"),Dimensions->getFloat("xScale"),Dimensions->getFloat("yScale"),Dimensions->getFloat("zScale"),fullfolder,Filename,Textures));
	}
	
	delete GroupFile;
}
