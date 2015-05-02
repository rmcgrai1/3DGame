// Piece.h
// Ryan McGrail

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "../Environmental.h"
#include "../../Primitives/Physical.h"
#include "../../Functions/mat4.h"

class Piece : public Environmental {
	
	public:
		Piece(int);															// Blueprint Constructors
		Piece(int, float,float,float);										
		~Piece();															// Deconstructor
		virtual void update(GraphicsOGL*, float);							// Updating
		void draw(GraphicsOGL*, float);										// Drawing
		virtual bool collide(Physical*);									// Colliding w/ Physical Object
		Piece* clone();														// Cloning Piece
		Piece* instantiate();												// Instantiating Piece, Top Level
		bool checkOnScreen(GraphicsOGL* gl);								// Checking if Piece is Onscreen
		void transformTranslation(float,float,float);						// Transforming Translation
		void transformScale(float);											// Transforming Scale Uniform
		void transformScale(float,float,float);								// Transforming Scale Nonuniform
		void transformRotationX(float);										// Transforming Rotation X
		void transformRotationY(float);										// Transforming Rotation Y
		void transformRotationZ(float);										// Transforming Rotation Z
		void damage(float);													// Damaging Piece
		Piece* addPiece(Piece*,float,float,float);							// Adding New Piece to Group, w/ Position
		Piece* addPiece(Piece*,float,float,float,float,float,float);		// Adding New Piece to Group, w/ Position & Rotation
		Piece* add3DWall(float,float,float,float,float,float);				// Adding 3D Wall to Group
		Piece* add3DFloor(float,float,float,float,float);					// Adding 3D Floor to Group
		Piece* add3DBlock(float,float,float,float,float,float);				// Adding 3D Block to Group

		static int P_WALL;													// Wall Type
		static int P_GROUP;													// Group Type
		static vector<Piece*> pieceList;									// List of Top-Level REAL Pieces

	protected:
		
		Piece(bool,float, float, float);									// REAL Piece Constructor
		bool collide(Physical*,mat4);										// Collision, Bottom Level
		Piece* instantiate(bool);											// Instiation, Bottom Level
		void draw(GraphicsOGL*, float, mat4);								// Drawing, Bottom Level
		Piece* addPiece(Piece*);											// Adding Piece to Group
		vector<Piece*> subpieces;											// Vector of Subpieces
		bool isInstance;													// Is NOT Blueprint?
		mat4 modelMat;														// Model Matrix
		int type;															// Type of Piece
		float w, h;															// Width/Height of Piece
};

#endif
