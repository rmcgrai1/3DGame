// SoundController.cpp
// Ryan McGrail

#include "SoundController.h"
#include "Sound.h"
#include <iostream>
#include "../Functions/Math2D.h"
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <string>
#include "../Characters/Character.h"
#include "../Environment/Environmental.h"
using namespace std;

// Static Variables
map<string, Sound*> SoundController :: soundMap;
float SoundController :: listenerX;
float SoundController :: listenerY;
float SoundController :: listenerZ;

// Constructor
SoundController :: SoundController(int argc, char** argv) {	
	
	// Initialize OpenAL
	alutInit(&argc, argv);

	// LOAD SOUNDS
	loadSound("musTwoson", "Resources/Music/Twoson.wav",.1);        
	loadSound("fsGrass", "Resources/Sounds/fsGrass.wav");        
	loadSound("swordSwing", "Resources/Sounds/swordSwing.wav",1.5);
	loadSound("text", "Resources/Sounds/text.wav",.25);        
	loadSound("death", "Resources/Sounds/death.wav",3);        
	loadSound("treeDamage", "Resources/Sounds/treeDamage.wav",.25);        
	loadSound("treeDie", "Resources/Sounds/treeDie.wav",0);        
	loadSound("heavyFall", "Resources/Sounds/heavyFall.wav",5);        
	loadSound("exploding", "Resources/Sounds/exploding.wav",3);        
	loadSound("swordHitFlesh", "Resources/Sounds/swordHitFlesh.wav",3);
	loadSound("swordHitWood", "Resources/Sounds/swordHitWood.wav",1.5);
	loadSound("attackCollision", "Resources/Sounds/attackCollision.wav",.1);

	// Play Music
	playMusic("musTwoson");
}

// Deconstructor
SoundController :: ~SoundController() {

	// Kill OpenAL & Alut
	kill();
}

// Clean Finished Sources
void SoundController :: cleanAll() {		
	for(int i = 0; i < soundList.size(); i++)
		soundList[i]->clean();
}

// Get Total Number of Sources Playing
int SoundController :: getNumPlaying() {
	int numPlaying = 0;
	
	for(int i = 0; i < soundList.size(); i++)
		numPlaying += soundList[i]->getNumPlaying();
	
	return numPlaying;
}
	
// Load Sound w/ Name
void SoundController :: loadSound(string name, string fileName) {
	loadSound(name, fileName, 1);
}

// Load Sound w/ Name, Volume
void SoundController :: loadSound(string name, string fileName, float volume) {
	Sound* snd = new Sound(fileName, volume);
	
	soundMap[name] = snd;
	soundList.push_back(snd);
}


// Play Sound as Music
ALuint SoundController :: playMusic(string name) {
	soundMap[name]->playMusic();
}

// Play Sound by Character
ALuint SoundController :: playSound(string name, Character* inst) {
	float x, y, z, vel, dir, vX, vY, vZ;

	// Get Character Position
	x = inst->getX();
	y = inst->getY();
	z = inst->getZ();

	//Get Character Velocity
	vel = inst->getVelocity();
	dir = inst->getDirection();

	vX = calcLenX(vel,dir);
	vY = calcLenY(vel,dir);
	vZ = 0;

	// Play Sound w/ Position, Velocity
	return playSound(name, x, y, z, vX, vY, vZ);
}

// Play Sound by Environmental
ALuint SoundController :: playSound(string name, Environmental* inst) {
	float x, y, z, vel, dir, vX, vY, vZ;

	// Get Position
	x = inst->getX();
	y = inst->getY();
	z = inst->getZ();

	// Play Sound w/ Position
	return playSound(name, x, y, z, 0,0,0);
}

// Play Sound w/ Position, Velocity
ALuint SoundController :: playSound(string name, double x, double y, double z, double vX, double vY, double vZ) {
	Sound* snd = soundMap[name];
	
	// Play Sound w/ Position if Sound Exists
	if(snd != NULL)
		return snd->playSound(x, y, z, vX, vY, vZ);
	else
		return -1;
}
	
// Play Sound, No Position
ALuint SoundController :: playSound(string name) {
	Sound* snd = soundMap[name];
	
	// If Sound Exists, Play Sound
	if(snd != NULL)
		return snd->playSound();
	else
		return -1;
}
	
// Update Listener Position
void SoundController :: updateListener(double cX, double cY, double cZ, double vX, double vY, double vZ, double nDirX, double nDirY, double nDirZ, double nUpX, double nUpY, double nUpZ) {

	// Position Camera (Fixes Sound Volume)
	cX *= POS_SCALE;
	cY *= POS_SCALE;
	cZ *= POS_SCALE;
	
	// Set Listener Position
	listenerX = cX;
	listenerY = cY;
	listenerZ = cZ;

	// Position of the listener.
	ALfloat listenerPos[] = {(float) cX, (float) cY, (float) cZ};

	// Velocity of the listener.
	ALfloat listenerVel[] = {(float) vX, (float) vY, (float) vZ};

	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat listenerOri[] = {(float) nDirX, (float) nDirY, (float) nDirZ,  (float) nUpX, (float) nUpY, (float) nUpZ};
		
	// Pass Values to OpenAL
	alListenerfv(AL_POSITION,    listenerPos);
	alListenerfv(AL_VELOCITY,    listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

// Kill All Sounds (When Done w/ Program)
void SoundController :: kill() {

	// Kill Sounds
	for(int i = 0; i < soundList.size(); i++)
		soundList[i]->kill();

	// Exit from Alut
	alutExit();
}