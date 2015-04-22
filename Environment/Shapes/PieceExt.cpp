// PieceExt.cpp

#include<iostream>
#include <iomanip>
#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../../Graphics/models/Model.h"
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
	gl->transformScale(xScale,yScale,zScale);
	gl->transformRotationX(xRot);
	gl->transformRotationY(yRot);
	gl->transformRotationZ(zRot);
	
	gl->transformTranslation(xIns,yIns,zIns);
	gl->transformScale(xScaleIns,yScaleIns,zScaleIns);
	gl->transformRotationX(xRotIns);
	gl->transformRotationY(yRotIns);
	gl->transformRotationZ(zRotIns);
	
	gl->draw3DModel(shape);
	
	gl->transformRotationZ(-1*zRotIns);
	gl->transformRotationY(-1*yRotIns);
	gl->transformRotationX(-1*xRotIns);
	gl->transformScale(1/xScaleIns,1/yScaleIns,1/zScaleIns);
	gl->transformTranslation(-1*xIns,-1*yIns,-1*zIns);
	
	gl->transformRotationZ(-1*zRot);
	gl->transformRotationY(-1*yRot);
	gl->transformRotationX(-1*xRot);
	gl->transformScale(1/xScale,1/yScale,1/zScale);
	gl->transformTranslation(-1*x,-1*y,-1*z);
}

void PieceExt::loadfromJSON() {
	string fullJSONpath = JSONdirectory + "/" + JSONfilename;
	JSON *GroupFile = new JSON(fullJSONpath);
	
	JSON *ModelJSON = GroupFile->getClass("model");
	string Folder = ModelJSON->getString("folder");
	string Filename = ModelJSON->getString("filename");
	string fullfolder = directory + "/" + Folder;
	JSON *Dimensions = ModelJSON->getClass("dimensions");
	xIns = Dimensions->getFloat("x");
	yIns = Dimensions->getFloat("y");
	zIns = Dimensions->getFloat("z");
	xRotIns = Dimensions->getFloat("xRot");
	yRotIns = Dimensions->getFloat("yRot");
	zRotIns = Dimensions->getFloat("zRot");
	xScaleIns = Dimensions->getFloat("xScale");
	yScaleIns = Dimensions->getFloat("yScale");
	zScaleIns = Dimensions->getFloat("zScale");
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
