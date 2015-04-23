// SmokeRing.cpp
// Ryan McGrail

#include <iostream>
#include "../Graphics/GraphicsOGL.h"
#include "SmokeRing.h"
#include "Particle.h"
using namespace std;


// Constructor
SmokeRing :: SmokeRing(float nX,float nY,float nZ,float startS,float endS,int nTotSteps, float myAlpha) : Particle(nX,nY,nZ) {

	// Initalize Size Variables
	startSize = curSize = startS;
	endSize = endS;

	// Initialize Animation Variables
	percDiv = nTotSteps;
	percSmoke = 1;

	// Relative Transparency (Small Hops = Small Alpha, Landing = Large Alpha)
	alpha = myAlpha;
}

// Update Function
void SmokeRing :: update(GraphicsOGL* gl, float deltaTime) {

	// Increase Size for Animation
	curSize += (endSize - curSize)/percDiv;

	// Decrease Alpha/Animate
	percSmoke += (0 - percSmoke)/percDiv;

	// If Done Animating, Destroy
	if(abs(curSize - endSize) < .01)
		destroy();
}

// Draw Function
void SmokeRing :: draw(GraphicsOGL* gl, float deltaTime) {

	// Get Floor Rotation from Heightmap
	float xyRot, setupRot;
	gl->getHeightmap()->getFloorRotations(x,y,setupRot,xyRot);

	// Clear Transformations
	gl->transformClear();
		// Translate to Position
		gl->transformTranslation(x,y,z);
	
		// Rotate to Ground
		gl->transformRotationZ(setupRot);	
		gl->transformRotationX(xyRot);
		gl->transformRotationZ(-setupRot);

		// If PC Not Slow, Enable Smoke Ring Shader
		if(!gl->isPCSlow()) {
			gl->enableShader("SmokeRing");
			
			// Pass Value Along to Animate Smoke
			gl->setShaderVariable("iSmoke", percSmoke*alpha);
		}
		
		// Draw as 3D Circle on Ground
		gl->draw3DCircle(0,0,.5,curSize,10);
		
		// Disable Shaders
		gl->disableShaders();

	// Clear Transformations
	gl->transformClear();
}
