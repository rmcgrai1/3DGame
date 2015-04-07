#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include "Sound.h"
#include <iostream>
#include <OpenAL/al.h>
#include <map>
#include <string>
#include <list>

using namespace std;

List<Sound> soundList = new ArrayList<Sound>();
Map<String, Sound> soundMap = new HashMap<String, Sound>();
AL al = ALFactory.getAL();

class SoundController {
private:
	float listenerX, listenerY, listenerZ;
public: 
	SoundController() {	
		//Initialize OpenAL
		ALut.alutInit();
        

        //LOAD SOUNDS
		loadSound("BlockCrumble", "Resources/Sounds/FX/sndBlockCrumble.wav");
        loadSound("Footstep", "Resources/Sounds/FX/sndFootstep.wav");
        loadSound("Spin", "Resources/Sounds/FX/sndSpin.wav");
        loadSound("Jump", "Resources/Sounds/FX/sndJump.wav", 50); 
        
        
        //Ensure that OpenAL Devices are Closed After Program Ends
        Runtime runtime = Runtime.getRuntime();
        runtime.addShutdownHook(
            new Thread(
                new Runnable() {
                    void run() {
                        kill();
                    }
                }
            )
        );
	}
	
	void cleanAll() {		
		for(Sound s : soundList)
			s.clean(al);
	}
	
	int getNumPlaying() {
		int numPlaying = 0;
		
		for(Sound s : soundList)
			numPlaying += s.getNumPlaying();
		
		return numPlaying;
	}
	
	
	void loadSound(String name, String fileName) {
		Sound snd = new Sound(al, fileName);
		
		soundMap.put(name, snd);
		soundList.add(snd);
	}
	
	void loadSound(String name, String fileName, float volume) {
		Sound snd = new Sound(al, fileName, volume);
		
		soundMap.put(name, snd);
		soundList.add(snd);
	}
	
	
	int[] playSound(String name, double x, double y, double z, double vX, double vY, double vZ) {
		Sound snd = soundMap.get(name);
		
		if(snd != null)
			return snd.playSound(al, x, y, z, vX, vY, vZ);
		else
			return null;
	}
	
	int[] playSound(String name) {
		return playSound(name, listenerX, listenerY, listenerZ, 0, 0, 0);
	}
	
	
	void updateListener(double cX, double cY, double cZ, double vX, double vY, double vZ, double nDirX, double nDirY, double nDirZ, double nUpX, double nUpY, double nUpZ) {
		// Position of the listener.
	    float[] listenerPos = {(float) cX, (float) cY, (float) cZ};

	    // Velocity of the listener.
	    float[] listenerVel = {(float) vX, (float) vY, (float) vZ};

	    // Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	    float[] listenerOri = {(float) nDirX, (float) nDirY, (float) nDirZ,  (float) nUpX, (float) nUpY, (float) nUpZ};
		
		al.alListenerfv(AL.AL_POSITION,	listenerPos, 0);
	    al.alListenerfv(AL.AL_VELOCITY,    listenerVel, 0);
	    al.alListenerfv(AL.AL_ORIENTATION, listenerOri, 0);
	}
	
	void kill() {
		for(Sound s : soundList)
			s.kill(al);
		ALut.alutExit();
	}

	void killSource(String name, int[] source) {
		soundMap.get(name).killSource(al, source);
	}
}

#endif
