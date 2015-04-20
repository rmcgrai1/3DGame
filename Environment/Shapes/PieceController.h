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
		int collide();
		void update(GraphicsOGL*, float);
		void damage(float);
		void newPieceGroup(string FileName);
	private:
		vector<PieceGroup *> AllPieceGroups;
		TexturePack *Textures;
};

#endif
