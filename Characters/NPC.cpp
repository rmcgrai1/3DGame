// NPC.cpp


#include <deque>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <string>
#include <iostream>
#include "../IO/InputController.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GraphicsOGL.h"
#include "Character.h"
#include "NPC.h"
#include <cmath>
#include "../Functions/Math2D.h"
#include "../Environment/Heightmap.h"
using namespace std;



NPC :: NPC(float x, float y, float z) : Character(x,y,z) {
}

void NPC :: update(GraphicsOGL* gl, float deltaTime) {

	Character :: update(gl, deltaTime);
}

void NPC :: draw(GraphicsOGL* gl, float deltaTime) {

	Character :: draw(gl, deltaTime);
}


void NPC :: land() {
}
