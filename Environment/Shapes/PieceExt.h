// PieceExt.h

#ifndef PIECEEXT_H
#define PIECEEXT_H

#include "../../Graphics/Models/Model.h"
#include "../../Graphics/GraphicsOGL.h"

class PieceExt : public Environmental {
	
	public:
		PieceExt(float x,float y,float z,float xrot,float yrot,float zrot);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
	private:
		float x;
		float y;
		float z;
		float xScale;
		float yScale;
		float zScale;
		float xRot;
		float yRot;
		float zRot;
};

#endif
