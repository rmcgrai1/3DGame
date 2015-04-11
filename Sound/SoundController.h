// SoundController.h

#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include "../Graphics/GraphicsOGL.h"
#include "Sound.h"
#include <iostream>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

class SoundController {
	public: 
		SoundController(int, char**);	
		~SoundController();

		void cleanAll();	
		int getNumPlaying();	
		void loadSound(string name, string fileName);
		void loadSound(string name, string fileName, float volume);	
		static ALuint playSound(string name, double x, double y, double z, double vX, double vY, double vZ);
		static ALuint playSound(string name);
		static ALuint playSound(string name,Character*);
		void updateListener(double cX, double cY, double cZ, double vX, double vY, double vZ, double nDirX, double nDirY, double nDirZ, double nUpX, double nUpY, double nUpZ);
		void kill();
		void killSource(string name, ALuint source);	

	private:
		static float listenerX, listenerY, listenerZ;
		static map<string, Sound*> soundMap;
		vector<Sound*> soundList;
};

#endif
