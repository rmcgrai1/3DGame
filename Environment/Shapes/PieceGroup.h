// PieceGroup.h

#ifndef PIECEGROUP_H
#define PIECEGROUP_H

class PieceGroup : public Piece {
	
	public:
		Piece();
		int collide();
		float calcFloorZ();

	protected:
		int pieceNum;
}

#endif
