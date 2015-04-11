// Sound.cpp

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


Sound :: Sound(string fileName) {
        valid = !(loadALData(fileName) == AL_FALSE);
	volume = 1;
}
    
Sound :: Sound(string fileName, float newVolume) {
        valid = !(loadALData(fileName) == AL_FALSE);
        volume = newVolume;
}
	

int Sound :: loadALData(string fileName) {

	const char* chName = fileName.c_str();
	ALbyte* name;
	name = (ALbyte*) malloc(sizeof(ALbyte) * (fileName.size()+1));

	for(int i = 0; i < fileName.size()+1; i++)
		name[i] = chName[i];


	alGenBuffers(1, &buffer);

	alutLoadWAVFile(name, &format, &data, &size, &freq, &loop);

	alBufferData(buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);


	free(name);

	if (alGetError() != AL_NO_ERROR) {

		return AL_FALSE;
	}
	else
		return true;
}


	    /*static void killALData() {
	        al.alDeleteBuffers(1, buffer, 0);
	        al.alDeleteSources(1, source, 0);
	        ALut.alutExit();
	    }*/
   

ALuint Sound :: playMusic() {
	ALuint src;    
		
        // Bind buffer with a source.
        alGenSources(1, &src);
        
        alSourcei (src, AL_BUFFER,   buffer);
        alSourcef (src, AL_GAIN,     volume);
        alSourcei (src, AL_LOOPING,  true);

        sources.push_back(src);
        
        playSound(src);
        
        return src;
}	    
	
void Sound :: playSound(ALuint src) {
	alSourcePlay(src);
}
	
void Sound :: playSound(int index) {
	alSourcePlay(sources[0]);
}
	
ALuint Sound :: playSound(double x, double y, double z, double vX, double vY, double vZ) {

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
        
        alSourcei (src, AL_BUFFER,   buffer);
        alSourcef (src, AL_PITCH,    1.0f + .5*(rnd()-.5));
        alSourcef (src, AL_GAIN,     volume);
        alSourcefv(src, AL_POSITION, sourcePos);
        alSourcefv(src, AL_VELOCITY, sourceVel);
        alSourcei (src, AL_LOOPING,  loop);

        sources.push_back(src);
        
        playSound(src);
        
        return src;
}
	    
void Sound :: pauseSound(int index) {
        alSourcePause(sources[0]);
}

void Sound :: stopSound(int index) {
        //alSourceStop(sources[0]);
}
	
	
void Sound :: clean() {
	vector<int> indices;
	vector<ALuint> toRemove;
	
	ALuint src;
	for(int i = 0; i < sources.size(); i++) {
		
		src = sources[i];			
		
		ALint state;
		    
		alGetSourcei(src, AL_SOURCE_STATE, &state);
		    
		if(state != AL_PLAYING) {
			indices.push_back(i);
			toRemove.push_back(src);
		}
	}
	
	for(int i = 0; i < toRemove.size(); i++) {
		alDeleteSources(1, &toRemove[i]);

		for(int j = 0; j < sources.size(); j++)
			if(toRemove[i] == sources[j]) {
				sources.erase(sources.begin()+j);
				break;
			}
	}
}

int Sound :: getNumPlaying() {
	return sources.size();
}

void Sound :: kill() {
	alDeleteBuffers(1, &buffer);

	for(int i = 0; i < sources.size(); i++)
		alDeleteSources(1, &sources[i]);
}

/*void Sound :: killSource(AL al*, ALuint src) {
	if(source.contains(src)) {
		al.alDeleteSources(1, src, 0);
		source.remove(src);
	}
}*/
