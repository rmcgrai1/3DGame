// Sound.h

#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>


#define POS_SCALE .025

using namespace std;

class Sound {

	public: 
		Sound(string fileName);
		Sound(string fileName, float volume);

		ALuint playMusic();
		void playSound(ALuint src);
		void playSound(int index);	
		ALuint playSound(double x, double y, double z, double vX, double vY, double vZ);
		void pauseSound(int index);
		void stopSound(int index);
		void clean();
		int getNumPlaying();

		void kill();
		void killSource(ALuint src);


	private:
		int loadALData(string fileName);
		void killALData();


		bool valid;	
		float volume;
	
		ALuint buffer;
		vector<ALuint> sources;

		ALenum format;
		ALsizei size;
		ALvoid* data;
		ALsizei freq;
		ALboolean loop;
};

#endif
