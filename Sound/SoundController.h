// SoundController.h
// Ryan McGrail

#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include "../Environment/Environmental.h"
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

class Environmental;
class SoundController {
	public: 
		SoundController(int, char**);																								// Constructor
		~SoundController();																											// Deconstructor

		void cleanAll();																											// Clean Sounds (Get Rid of Finished Sources)
		int getNumPlaying();																										// Get Number of Sources Playing
		void loadSound(string name, string fileName);																				// Load Sound
		void loadSound(string name, string fileName, float volume);																	// Load Sound (Specifying Volume)
		static ALuint playMusic(string name);																						// Play Music (Loops)
		static ALuint playSound(string name, double x, double y, double z, double vX, double vY, double vZ);						// Play Sound from Position
		static ALuint playSound(string name);																						// Play Sound
		static ALuint playSound(string name,Character*);																			// Play Sound by Character Object
		static ALuint playSound(string name,Environmental*);																		// Play Sound by Environmental Object
		void updateListener(double, double, double, double, double, double, double, double, double, double, double, double);		// Update Listener Position
		void kill();																												// Kill all Sounds

	private:
		static float listenerX, listenerY, listenerZ;																				// Listener Position
		static map<string, Sound*> soundMap;																						// Map of Sounds
		vector<Sound*> soundList;																									// List of Sounds
};

#endif
