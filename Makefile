all: main

main: main.o Math2D.o Particle.o SmokeRing.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o TexturePack.o TextureController.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Character.o Player.o NPC.o Environmental.o Terrain.o Heightmap.o Water.o Tree.o PineTree.o Branch.o FileIO.o InputController.o playerInv.o menu.o inventory.o invslot.o item.o FrameTexture.o PosSpec.o TextController.o TextInterpreter.o SoundController.o Sound.o Data/SortedList.h DirtPath.o Bush.o Model.o Pos3D.o Face.o Mtl.o DeathPuff.o
	g++ main.o Math2D.o Particle.o SmokeRing.o GraphicsOGL.o Camera.o Image.o Texture.o TextureExt.o TexturePack.o TextureController.o FontController.o Font.o ShaderController.o Shader.o Updateable.o Drawable.o Instantiable.o Physical.o Character.o Player.o NPC.o Environmental.o Terrain.o Heightmap.o Water.o Tree.o PineTree.o Branch.o FileIO.o InputController.o playerInv.o menu.o inventory.o invslot.o item.o FrameTexture.o PosSpec.o TextController.o TextInterpreter.o Data/SortedList.h DirtPath.o Bush.o Sound.o SoundController.o Model.o Pos3D.o Face.o Mtl.o DeathPuff.o -o main -lglut -lGLU -lGL -lX11 -lpthread -lpng -lalut -lopenal

main.o: main.cpp
	g++ -c main.cpp



# MENUS
###############################################################
menu.o: menus/menu.cpp menus/menu.h menus/playerInv.h Primitives/Drawable.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c menus/menu.cpp -o menu.o

inventory.o: menus/inventory.cpp menus/inventory.h menus/invslot.h menus/item.h Primitives/Drawable.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c menus/inventory.cpp -o inventory.o

playerInv.o: menus/playerInv.cpp menus/playerInv.h menus/invslot.h menus/item.h Primitives/Drawable.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c menus/playerInv.cpp -o playerInv.o

invslot.o: menus/invslot.cpp menus/invslot.h menus/item.h Graphics/GraphicsOGL.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c menus/invslot.cpp -o invslot.o -std=c++11

item.o: menus/item.cpp menus/item.h Graphics/Texture.h Graphics/TexturePack.h
	g++ -c menus/item.cpp -o item.o

FrameTexture.o: menus/FrameTexture.cpp menus/FrameTexture.h Graphics/Texture.h Graphics/TexturePack.h Graphics/GraphicsOGL.h
	g++ -c menus/FrameTexture.cpp -o FrameTexture.o -std=c++11

PosSpec.o: menus/PosSpec.cpp menus/PosSpec.h
	g++ -c menus/PosSpec.cpp -o PosSpec.o


# FUNCTIONS
###############################################################
Math2D.o: Functions/Math2D.cpp Functions/Math2D.h
	g++ -c Functions/Math2D.cpp -std=c++11



# PARTICLES
###############################################################
Particle.o: Particles/Particle.cpp Particles/Particle.h
	g++ -c Particles/Particle.cpp

SmokeRing.o: Particles/SmokeRing.cpp Particles/SmokeRing.h
	g++ -c Particles/SmokeRing.cpp
DeathPuff.o: Particles/DeathPuff.cpp Particles/DeathPuff.h
	g++ -c Particles/DeathPuff.cpp


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


# MODELS
###############################################################
Model.o: Graphics/models/Model.cpp Graphics/models/Model.h Graphics/models/Pos3D.h Graphics/models/Face.h Graphics/models/Mtl.h
	g++ -c Graphics/models/Model.cpp
Pos3D.o: Graphics/models/Pos3D.cpp Graphics/models/Pos3D.h
	g++ -c Graphics/models/Pos3D.cpp
Face.o: Graphics/models/Face.cpp Graphics/models/Face.h Graphics/models/Pos3D.h Graphics/models/Mtl.h
	g++ -c Graphics/models/Face.cpp
Mtl.o: Graphics/models/Mtl.cpp Graphics/models/Mtl.h
	g++ -c Graphics/models/Mtl.cpp

# PRIMITIVES
###############################################################
Updateable.o: Primitives/Updateable.cpp Primitives/Updateable.h
	g++ -c Primitives/Updateable.cpp -std=c++11
Drawable.o: Primitives/Drawable.cpp Primitives/Drawable.h Data/SortedList.h
	g++ -c Primitives/Drawable.cpp Data/SortedList.h
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
Environmental.o: Environment/Environmental.cpp Environment/Environmental.h
	g++ -c Environment/Environmental.cpp
Terrain.o: Environment/Terrain.cpp Environment/Terrain.h
	g++ -c Environment/Terrain.cpp
Heightmap.o: Environment/Heightmap.cpp Environment/Heightmap.h
	g++ -c Environment/Heightmap.cpp
Water.o: Environment/Water.cpp Environment/Water.h
	g++ -c Environment/Water.cpp
Tree.o: Environment/Tree.cpp Environment/Tree.h
	g++ -c Environment/Tree.cpp -std=c++11
PineTree.o: Environment/PineTree.cpp Environment/PineTree.h
	g++ -c Environment/PineTree.cpp
Bush.o: Environment/Bush.cpp Environment/Bush.h
	g++ -c Environment/Bush.cpp
Branch.o: Environment/Branch.cpp Environment/Branch.h
	g++ -c Environment/Branch.cpp
DirtPath.o: Environment/DirtPath.cpp Environment/DirtPath.h
	g++ -c Environment/DirtPath.cpp


# INPUT/OUTPUT
###############################################################
FileIO.o: IO/FileIO.cpp IO/FileIO.h
	g++ -c IO/FileIO.cpp

InputController.o: IO/InputController.cpp IO/InputController.h
	g++ -c IO/InputController.cpp

# TEXT
###############################################################
TextController.o: Text/TextController.cpp Text/TextController.h
	g++ -c Text/TextController.cpp -std=c++11

TextInterpreter.o: Text/TextInterpreter.cpp Text/TextInterpreter.h
	g++ -c Text/TextInterpreter.cpp -std=c++11


# SOUND
###############################################################
SoundController.o: Sound/SoundController.cpp Sound/SoundController.h Sound.o
	g++ -c Sound/SoundController.cpp

Sound.o: Sound/Sound.cpp Sound/Sound.h
	g++ -c Sound/Sound.cpp

clean:
	rm *.o main
