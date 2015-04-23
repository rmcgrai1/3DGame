// Sound.h
// Ryan McGrail

#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
using namespace std;

// Define Scaling for Position (to Fix Sounds that were Too Quiet)
#define POS_SCALE .025


class Sound {

	public: 
		Sound(string fileName);																// Load Sound from File
		Sound(string fileName, float volume);												// Load Sound from File, Set Volume

		ALuint playMusic();																	// Play as Music (Looping)
		ALuint playSound();																	// Play Sound w/o Source, Position
		void playSound(ALuint src);															// Play Sound w/ Source
		void playSound(int index);															// Play Sound at Index
		ALuint playSound(double x, double y, double z, double vX, double vY, double vZ);	// Play Sound at Position, with Velocity
		void pauseSound(int index);															// Pause Sound at Index
		void stopSound(int index);															// Stop Sound at Index
		void clean();																		// Remove Sources that Stopped Playing
		int getNumPlaying();																// Get # of this Sound Playing Currently

		void kill();																		// Kill all Sources
		void killSource(ALuint src);														// Kill Specific Source


	private:
		int loadALData(string fileName);													// Load AL Data from File
		void killALData();																	// Delete AL Data


		bool valid;																			// If Sound Exists, Can be Played
		float volume;																		// Volume
	
		ALuint buffer;																		// Sound Buffer
		vector<ALuint> sources;																// List of Sources

		ALenum format;																		// File Format of Sound
		ALsizei size;																		// Size of Data
		ALvoid* data;																		// Pointer to Data
		ALsizei freq;																		// Frequency (Pitch) of Sound
		ALboolean loop;																		// Whether or not the Sound Loops
};

#endif
