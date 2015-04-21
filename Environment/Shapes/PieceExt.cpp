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
	loadfromJSON();
}

void PieceExt::update(GraphicsOGL* gl, float deltaTime) {
	
}
void PieceExt::draw(GraphicsOGL* gl, float deltaTime) {
	
}

void PieceExt::loadfromJSON() {
	string fullJSONpath = JSONdirectory + "/" + JSONfilename;
	JSON *GroupFile = new JSON(fullJSONpath);
	
	JSON *Dimensions = GroupFile->getClass("dimensions");
	string Folder = GroupFile->getString("folder");
	string Filename = GroupFile->getString("filename");
	string fullfolder = JSONdirectory + "/" + Folder;
	vector<JSON *> PiecesJSON = GroupFile->getClassArray("Pieces");
	vector<JSON *>::iterator i;
	for(i=PiecesJSON.begin();i!=PiecesJSON.end();i++) {
		JSON *PieceDimension = (*i)->getClass("dimensions");
		string PieceType = (*i)->getString("type");
		// add a Piece of this type in this position
	}
	
	delete GroupFile;
}