// Sound.cpp
// Ryan McGrail

#include <iostream>
#include <stdlib.h>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include "../Functions/Math2D.h"
#include "Sound.h"
#include <string>
#include <vector>


using namespace std;


// Constructor, FileName
Sound :: Sound(string fileName) {
    valid = !(loadALData(fileName) == AL_FALSE);
	volume = 1;
}

// Constructor, FileName & Fractional Volume    
Sound :: Sound(string fileName, float newVolume) {
	valid = !(loadALData(fileName) == AL_FALSE);
	volume = newVolume;
}
	
	
// Loading Sound File
int Sound :: loadALData(string fileName) {

	const char* chName = fileName.c_str();
	
	// Get Name as ALbyte Array (Required for alutLoadWAVFile())
	ALbyte* name;
	name = (ALbyte*) malloc(sizeof(ALbyte) * (fileName.size()+1));
	for(int i = 0; i < fileName.size()+1; i++)
		name[i] = chName[i];


	// Generate Buffer for Sound, Load into Buffer
	alGenBuffers(1, &buffer);

	alutLoadWAVFile(name, &format, &data, &size, &freq, &loop);

	alBufferData(buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);


	// Free Name ALbyte Array
	free(name);

	// If Error, Sound is NOT Valid!!	
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;
	else
		return true;
}


// Playing Sound as Music
ALuint Sound :: playMusic() {
	ALuint src;    
		
	// Bind buffer with a source.
	alGenSources(1, &src);
	
	// Set up Source for Playing Music
	alSourcei (src, AL_BUFFER,   buffer);
	alSourcef (src, AL_GAIN,     volume);
	alSourcei (src, AL_LOOPING,  true);

	// Create Source, Play
	sources.push_back(src);
	playSound(src);
	
	return src;
}	    

// Play Source
void Sound :: playSound(ALuint src) {
	alSourcePlay(src);
}
	
// Play Sound Normally
ALuint Sound :: playSound() {
	ALuint src;
					    
	// Bind buffer with a source.
	alGenSources(1, &src);
	
	// Setup OpenAL for Playing Sound
	alSourcei (src, AL_BUFFER,   buffer);
	alSourcef (src, AL_PITCH,    1.0f);
	alSourcef (src, AL_GAIN,     volume);
	alSourcei (src, AL_LOOPING,  loop);

	// Add New Source, Play
	sources.push_back(src);
	playSound(src);
	
	return src;
}


// Play Sound from Position
ALuint Sound :: playSound(double x, double y, double z, double vX, double vY, double vZ) {

	// Position Coordinates Properly (Need to Scale Down, So Camera is "Closer")
	x *= POS_SCALE;
	y *= POS_SCALE;
	z *= POS_SCALE;

	ALuint src;
				
	// Position of the source sound.
	ALfloat sourcePos[] = {(float) x, (float) y, (float) z};

	// Velocity of the source sound.
	ALfloat sourceVel[] = {(float) vX, (float) vY, (float) vZ};
	    	
	// Bind buffer with a source.
	alGenSources(1, &src);
	
	// Set up Buffer, Pitch, Position, Velocity, Etc.
	alSourcei (src, AL_BUFFER,   buffer);
	alSourcef (src, AL_PITCH,    1.0f + .5*(rnd()-.5));
	alSourcef (src, AL_GAIN,     volume);
	alSourcefv(src, AL_POSITION, sourcePos);
	alSourcefv(src, AL_VELOCITY, sourceVel);
	alSourcei (src, AL_LOOPING,  loop);

	// Create Source, Play
	sources.push_back(src); 
	playSound(src);
	
	return src;
}
	

// "Clean" Sound so Vector Only Contains those Playing
void Sound :: clean() {
	vector<ALuint> toRemove;
	ALuint src;
	ALint state;

	for(int i = 0; i < sources.size(); i++) {
	
		// Get Source from List
		src = sources[i];			
		    
		// Get State of Sound
		alGetSourcei(src, AL_SOURCE_STATE, &state);
		    
		// If Sound State is Not AL_PLAYING, Done Playing, We Should Remove Sound
		if(state != AL_PLAYING)
			toRemove.push_back(src);
	}
	
	// Loop through Sources to Remove
	for(int i = 0; i < toRemove.size(); i++) {
		// Delete Source
		alDeleteSources(1, &toRemove[i]);

		// Find Source in Original List
		for(int j = 0; j < sources.size(); j++)
			// Remove Source from Lists
			if(toRemove[i] == sources[j]) {
				sources.erase(sources.begin()+j);
				break;
			}
	}
}

// Get # of Instances of this Sound Playing
int Sound :: getNumPlaying() {
	return sources.size();
}

// Kill Sound, Forever
void Sound :: kill() {
	// Delete Buffer that Stores WAV
	alDeleteBuffers(1, &buffer);

	// Delete all Sources
	for(int i = 0; i < sources.size(); i++)
		alDeleteSources(1, &sources[i]);
}