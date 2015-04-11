// Controller.h


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IO/InputController.h"
#include "Graphics/TextureController.h"
#include "Graphics/ShaderController.h"
#include "Graphics/FontController.h"
#include "Graphics/GraphicsOGL.h"
#include "Environment/Heightmap.h"

class GraphicsOGL;
class Heightmap;
class Controller {
	public:
		Controller(int, char* []);
		~Controller();

		void initialize(GraphicsOGL*);


			GraphicsOGL* getGraphicsOGL();
			InputController* getInputController();
			Heightmap* getHeightmap();
			TextureController* getTextureController();
			ShaderController* getShaderController();
			FontController* getFontController();

	private:

			GraphicsOGL* gl;

		//Heightmap Variables
			Heightmap* curHeightmap;

		//Input Variables
			
			
};

#endif
