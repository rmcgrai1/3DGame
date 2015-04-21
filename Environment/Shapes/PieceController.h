// PieceController.h

#ifndef PIECECONTROLLER_H
#define PIECECONTROLLER_H

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include <vector>
class PieceGroup;//#include "PieceGroup.h"
#include "../../Primitives/Updateable.h"

using namespace std;
class PieceController : public Updateable {
	
	public:
		PieceController();
		void update(GraphicsOGL*, float);
		void newPieceGroup(float x,float y,float z,string location);
		void newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,string location);
		void newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,float xScale,float yScale,float zScale,string location);
		void newPieceGroup(float x,float y,float z,string location,string filename);
		void newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,string location,string filename);
		void newPieceGroup(float x,float y,float z,float xRot,float yRot,float zRot,float xScale,float yScale,float zScale,string location,string filename);
	private:
		vector<PieceGroup *> AllPieceGroups;
		TexturePack *Textures;
};

#endif
