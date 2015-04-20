// PieceGroup.h

#ifndef PIECEGROUP_H
#define PIECEGROUP_H

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "../Environmental.h"

class PieceGroup : public Environmental {
	
	public:
		PieceGroup(float new_x=0,float new_y=0,float new_z=0,float new_xRot=0,float new_yRot=0,float new_zRot=0,float new_xScale=1,float new_yScale=1,float new_zScale=1,string location="Resources/Structures/Default",TexturePack *TP = new TexturePack);
		PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,float new_xScale,float new_yScale,float new_zScale,string location,string filename,TexturePack *TP);
		PieceGroup(float new_x,float new_y,float new_z,float new_xRot,float new_yRot,float new_zRot,string location,TexturePack *TP);
		PieceGroup(float new_x,float new_y,float new_z,string location,TexturePack *TP);
		int collide();
		float calcFloorZ();
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
		void damage(float);
	private:
		void loadfromJSON();
		
		TexturePack *Textures;
		string JSONdirectory;
		string JSONfilename;
		
		float x,y,z;
		float xRot,yRot,zRot;
		float xScale,yScale,zScale;
};

#endif
