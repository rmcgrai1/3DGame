// PieceExt.cpp

#include<iostream>
#include <iomanip>
#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/Models/Model.h"
#include "../../JSON/JSON.h"
#include "PieceExt.h"

PieceExt::PieceExt(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,string filename,TexturePack *TP) {
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
}

void PieceExt::update(GraphicsOGL* gl, float deltaTime) {
	
}
void PieceExt::draw(GraphicsOGL* gl, float deltaTime) {
	gl->transformTranslation(x,y,z);
	gl->transformRotationX(xRot);
	gl->transformRotationY(yRot);
	gl->transformRotationZ(zRot);
	gl->transformScale(xScale,yScale,zScale);
	
	gl->draw3DModel(shape);
	
	gl->transformScale(1/xScale,1/yScale,1/zScale);
	gl->transformRotationZ(-1*zRot);
	gl->transformRotationY(-1*yRot);
	gl->transformRotationX(-1*xRot);
	gl->transformTranslation(-1*x,-1*y,-1*z);
}

void PieceExt::loadfromJSON() {
	string fullJSONpath = JSONdirectory + "/" + JSONfilename;
	JSON *GroupFile = new JSON(fullJSONpath);
	
	JSON *ModelJSON = GroupFile->getClass("model");
	string Folder = ModelJSON->getString("folder");
	string Filename = ModelJSON->getString("filename");
	string fullfolder = directory + "/" + Folder;
	shape = new Model(fullfolder,Filename,Textures); // get model from file
	vector<JSON *> PiecesJSON = GroupFile->getClassArray("Pieces");
	vector<JSON *>::iterator i;
	for(i=PiecesJSON.begin();i!=PiecesJSON.end();i++) {
		JSON *PieceDimension = (*i)->getClass("dimensions");
		string PieceType = (*i)->getString("type");
		// add a Piece of this type in this position
	}
	
	delete GroupFile;
}