// PieceController.cpp

#include "../../Graphics/GraphicsOGL.h"
#include "../../Graphics/TexturePack.h"
#include "PieceController.h"
#include <stdlib.h>
#include "PieceGroup.h"

PieceController::PieceController() : Updateable() {
	Textures = new TexturePack;
	AllPieceGroups.push_back(new PieceGroup(200,200,0,"Resources/Structures/Default",Textures));
}

int PieceController::collide() {
	
}

void PieceController::update(GraphicsOGL* gl, float deltaTime) {
	cout << "Updating PieceController\n";
}

void PieceController::damage(float amount) {
	
}

void PieceController::newPieceGroup(string FileName) {
	
}