all: main

main: main.o Math2D.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o TexturePack.o TextureController.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Character.o Player.o NPC.o Terrain.o Heightmap.o Water.o Tree.o Branch.o FileIO.o InputController.o inventory.o invslot.o item.o
	g++ main.o Math2D.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o TexturePack.o TextureController.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Character.o Player.o NPC.o Terrain.o Heightmap.o Water.o Tree.o Branch.o FileIO.o InputController.o inventory.o invslot.o item.o -o main -lglut -lGLU -lGL -lX11 -lpthread -lpng

main.o: main.cpp
	g++ -c main.cpp



# INVENTORY
###############################################################
inventory.o: inventory/inventory.cpp inventory/inventory.h inventory/invslot.h inventory/item.h Primitives/Drawable.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c inventory/inventory.cpp -o inventory.o

invslot.o: inventory/invslot.cpp inventory/invslot.h inventory/item.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c inventory/invslot.cpp -o invslot.o

item.o: inventory/item.cpp inventory/item.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c inventory/item.cpp -o item.o


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
TexturePack.o: Graphics/TexturePack.cpp Graphics/TexturePack.h Graphics/Texture.h
	g++ -c Graphics/TexturePack.cpp
TextureController.o: Graphics/TextureController.cpp Graphics/TextureController.h
	g++ -c Graphics/TextureController.cpp

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

Character.o: Characters/Character.cpp Characters/Character.h
	g++ -c Characters/Character.cpp -std=c++11
Player.o: Characters/Player.cpp Characters/Player.h
	g++ -c Characters/Player.cpp -std=c++11
NPC.o: Characters/NPC.cpp Characters/NPC.h
	g++ -c Characters/NPC.cpp -std=c++11


# ENVIRONMENT
###############################################################
Terrain.o: Environment/Terrain.cpp Environment/Terrain.h
	g++ -c Environment/Terrain.cpp
Heightmap.o: Environment/Heightmap.cpp Environment/Heightmap.h
	g++ -c Environment/Heightmap.cpp
Water.o: Environment/Water.cpp Environment/Water.h
	g++ -c Environment/Water.cpp
Tree.o: Environment/Tree.cpp Environment/Tree.h
	g++ -c Environment/Tree.cpp
Branch.o: Environment/Branch.cpp Environment/Branch.h
	g++ -c Environment/Branch.cpp


# INPUT/OUTPUT
###############################################################
FileIO.o: IO/FileIO.cpp IO/FileIO.h
	g++ -c IO/FileIO.cpp

InputController.o: IO/InputController.cpp IO/InputController.h
	g++ -c IO/InputController.cpp


clean:
	rm *.o main
