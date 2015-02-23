all: main

main: main.o GraphicsOGL.o Texture.o TextureExt.o Font.o Shader.o FileIO.o
	g++ `Magick++-config --with-png --cxxflags --cppflags` main.o GraphicsOGL.o Texture.o TextureExt.o Font.o Shader.o FileIO.o -o main -lglut -lGL `Magick++-config --ldflags --libs`

main.o: main.cpp
	g++ -c main.cpp


# GRAPHICS
###############################################################
GraphicsOGL.o: Graphics/GraphicsOGL.cpp Graphics/GraphicsOGL.h
	g++ -c Graphics/GraphicsOGL.cpp
Texture.o: Graphics/Texture.cpp Graphics/Texture.h
	g++ -c -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 Graphics/Texture.cpp
TextureExt.o: Graphics/TextureExt.cpp Graphics/TextureExt.h
	g++ -c Graphics/TextureExt.cpp

Font.o: Graphics/Font.cpp Graphics/Font.h
	g++ -c Graphics/Font.cpp
	
Shader.o: Graphics/Shader.cpp Graphics/Shader.h
	g++ -c Graphics/Shader.cpp



# INPUT/OUTPUT
###############################################################
FileIO.o: IO/FileIO.cpp IO/FileIO.h
	g++ -c IO/FileIO.cpp




clean:
	rm *.o main
