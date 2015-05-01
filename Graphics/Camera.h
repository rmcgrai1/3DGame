// Camera.h
// Ryan McGrail

#ifndef CAMERA_H
#define CAMERA_H

#include "GraphicsOGL.h"
 	
class GraphicsOGL;
class Camera {
	public:
		Camera();																			// Constructor
		float getCamDir();																	// Get XY Direction of Camera
		void setProjection(GraphicsOGL*);													// Set Projection
		void setProjectionPrep(float, float, float, float, float, float);					// Prep Values for Setting Projection

		float getX();																		// Get X Position of Camera
		float getY();																		// Get Y Position of Camera
		float getZ();																		// Get Z Position of Camera

		void getNormal(float[3]);															// Get XYZ Direction of Camera, Normalized
		void getPosition(float[3]);															// Get XYZ Position of Camera
		void getShaderPosition(float[3]);													// Get XYZ Position of Camera for Shaders (Water Shader)
		void getDirection(float[3]);														// Get XYZ Direction of Camera for Shaders

	private:

		float camX;																			// CURRENT Position of Camera
		float camY;
		float camZ;

		float toX;																			// CURRENT Position Camera is Looking At
		float toY;
		float toZ;

		float focusZ;																		// NEW Position Camera will be Looking At, Z (To Smoothly Move Camera Focus)
		float newCamZ;																		// New Position of Camera, Z (To Smoothly Move Camera)

		float camDir;																		// XY Direction of Camera
};

#endif
