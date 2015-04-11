// SoundController.cpp


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
using namespace std;

map<string, Sound*> SoundController :: soundMap;
float SoundController :: listenerX;
float SoundController :: listenerY;
float SoundController :: listenerZ;

/*List<Sound> soundList = new ArrayList<Sound>();
Map<String, Sound> soundMap = new HashMap<String, Sound>();
AL al = ALFactory.getAL();*/

SoundController :: SoundController(int argc, char** argv) {	
	//Initialize OpenAL
	alutInit(&argc, argv);

        //LOAD SOUNDS
        loadSound("musTwoson", "Resources/Music/Twoson.wav",.3);        
        loadSound("fsGrass", "Resources/Sounds/fsGrass.wav");        
        loadSound("swordSwing", "Resources/Sounds/swordSwing.wav",1.5);        
	loadSound("death", "Resources/Sounds/death.wav",3);        
	loadSound("exploding", "Resources/Sounds/exploding.wav",3);        
        loadSound("swordHitFlesh", "Resources/Sounds/swordHitFlesh.wav",3);
        loadSound("swordHitWood", "Resources/Sounds/swordHitWood.wav",1.5);
	loadSound("attackCollision", "Resources/Sounds/attackCollision.wav",.1);

	playMusic("musTwoson");        
}

SoundController :: ~SoundController() {
	kill();
}
	
void SoundController :: cleanAll() {		
	for(int i = 0; i < soundList.size(); i++)
		soundList[i]->clean();
}
	
int SoundController :: getNumPlaying() {
	int numPlaying = 0;
	
	for(int i = 0; i < soundList.size(); i++)
		numPlaying += soundList[i]->getNumPlaying();
	
	return numPlaying;
}
	
	
void SoundController :: loadSound(string name, string fileName) {
	loadSound(name, fileName, 1);
}
	
void SoundController :: loadSound(string name, string fileName, float volume) {
	Sound* snd = new Sound(fileName, volume);
	
	soundMap[name] = snd;
	soundList.push_back(snd);
}

	
ALuint SoundController :: playMusic(string name) {
	soundMap[name]->playMusic();
}

ALuint SoundController :: playSound(string name, Character* inst) {
	float x, y, z, vel, dir, vX, vY, vZ;
	x = inst->getX();
	y = inst->getY();
	z = inst->getZ();

	vel = inst->getVelocity();
	dir = inst->getDirection();

	vX = calcLenX(vel,dir);
	vY = calcLenY(vel,dir);
	vZ = 0;

	return playSound(name, x, y, z, vX, vY, vZ);
}	
ALuint SoundController :: playSound(string name, double x, double y, double z, double vX, double vY, double vZ) {
	Sound* snd = soundMap[name];
	
	if(snd != NULL)
		return snd->playSound(x, y, z, vX, vY, vZ);
	else
		return -1;
}
	
ALuint SoundController :: playSound(string name) {
	return playSound(name, listenerX, listenerY, listenerZ, 0, 0, 0);
}
	
	
void SoundController :: updateListener(double cX, double cY, double cZ, double vX, double vY, double vZ, double nDirX, double nDirY, double nDirZ, double nUpX, double nUpY, double nUpZ) {

	cX *= POS_SCALE;
	cY *= POS_SCALE;
	cZ *= POS_SCALE;

	listenerX = cX;
	listenerY = cY;
	listenerZ = cZ;

	// Position of the listener.
	ALfloat listenerPos[] = {(float) cX, (float) cY, (float) cZ};

	// Velocity of the listener.
	ALfloat listenerVel[] = {(float) vX, (float) vY, (float) vZ};

	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat listenerOri[] = {(float) nDirX, (float) nDirY, (float) nDirZ,  (float) nUpX, (float) nUpY, (float) nUpZ};
		
	alListenerfv(AL_POSITION,    listenerPos);
	alListenerfv(AL_VELOCITY,    listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
}
	
void SoundController :: kill() {
	for(int i = 0; i < soundList.size(); i++)
		soundList[i]->kill();
	alutExit();
}

void SoundController :: killSource(string name, ALuint source) {
	//soundMap[name]->killSource(source);
}
