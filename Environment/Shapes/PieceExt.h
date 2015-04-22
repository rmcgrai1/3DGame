// PieceExt.h

#ifndef PIECEEXT_H
#define PIECEEXT_H

#include "../../Graphics/models/Model.h"
#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../../JSON/JSON.h"

class PieceExt {
	
	public:
		PieceExt(float new_x=0,float new_y=0,float new_z=0,float new_xRot=0,float new_yRot=0,float new_zRot=0,float new_xScale=1,float new_yScale=1,float new_zScale=1,string location="Resources/Structures/Default/PieceExt1",string filename="model.json",TexturePack *TP = new TexturePack);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
	private:
		void loadfromJSON();
		
		TexturePack *Textures;
		string JSONdirectory;
		string JSONfilename;
		string directory;
		string TPfolder;
		Model *shape;
		
		float x,y,z;
		float xRot,yRot,zRot;
		float xScale,yScale,zScale;
		
		float xIns,yIns,zIns;
		float xRotIns,yRotIns,zRotIns;
		float xScaleIns,yScaleIns,zScaleIns;
};

#endif
