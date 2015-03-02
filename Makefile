all: main

main: main.o Math2D.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Player.o Heightmap.o FileIO.o InputController.o
	g++ main.o Math2D.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Player.o Heightmap.o FileIO.o InputController.o -o main -lglut -lGLU -lGL -lX11 -lpthread -lpng

main.o: main.cpp
	g++ -c main.cpp

# FUNCTIONS
###############################################################
Math2D.o: Functions/Math2D.cpp Functions/Math2D.h
	g++ -c Functions/Math2D.cpp



# GRAPHICS
###############################################################
GraphicsOGL.o: Graphics/GraphicsOGL.cpp Graphics/GraphicsOGL.h
	g++ -c Graphics/GraphicsOGL.cpp -std=c++11

Camera.o: Graphics/Camera.cpp Graphics/Camera.h
	g++ -c Graphics/Camera.cpp

Image.o: Graphics/Image.cpp Graphics/Image.h
	g++ -c Graphics/Image.cpp -lX11 -lpthread -lpng

Texture.o: Graphics/Texture.cpp Graphics/Texture.h
	g++ -c Graphics/Texture.cpp
TextureExt.o: Graphics/TextureExt.cpp Graphics/TextureExt.h
	g++ -c Graphics/TextureExt.cpp

FontController.o: Graphics/Font.cpp Graphics/FontController.h
	g++ -c Graphics/FontController.cpp
Font.o: Graphics/Font.cpp Graphics/Font.h
	g++ -c Graphics/Font.cpp

ShaderController.o: Graphics/ShaderController.cpp Graphics/ShaderController.h
	g++ -c Graphics/ShaderController.cpp	
Shader.o: Graphics/Shader.cpp Graphics/Shader.h
	g++ -c Graphics/Shader.cpp


# PRIMITIVES
###############################################################
Updateable.o: Primitives/Updateable.cpp Primitives/Updateable.h
	g++ -c Primitives/Updateable.cpp
Drawable.o: Primitives/Drawable.cpp Primitives/Drawable.h
	g++ -c Primitives/Drawable.cpp
Instantiable.o: Primitives/Instantiable.cpp Primitives/Instantiable.h
	g++ -c Primitives/Instantiable.cpp
Physical.o: Primitives/Physical.cpp Primitives/Physical.h
	g++ -c Primitives/Physical.cpp


# CHARACTERS
###############################################################


Player.o: Characters/Player.cpp Characters/Player.h
	g++ -c Characters/Player.cpp -std=c++11


# ENVIRONMENT
###############################################################
Heightmap.o: Environment/Heightmap.cpp Environment/Heightmap.h
	g++ -c Environment/Heightmap.cpp


# INPUT/OUTPUT
###############################################################
FileIO.o: IO/FileIO.cpp IO/FileIO.h
	g++ -c IO/FileIO.cpp

InputController.o: IO/InputController.cpp IO/InputController.h
	g++ -c IO/InputController.cpp


clean:
	rm *.o main
