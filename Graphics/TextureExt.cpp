// TextureExt.cpp


#include <string>
#include <vector>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "TextureExt.h"
#include "Texture.h"
#include "GraphicsOGL.h"
#include "../Functions/Math2D.h"
using namespace std;



TextureExt :: TextureExt(Texture * tex) {

	addFrame(tex);
}


TextureExt :: TextureExt(string fileName) {

	if(!fileName.find(".")) {
		loadDirectory(fileName);
	}
	else
		addFrame(fileName);
}

void TextureExt :: loadDirectory(string dirName) {

	/*DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (dirName)) != NULL) {
		while ((ent = readdir (dir)) != NULL)
			addFrame(ent->d_name);
		closedir (dir);
	} else {
		perror ("");
		return EXIT_FAILURE;
	}*/
}


void TextureExt :: bind(int ind) {
	getFrame(ind)->bind();
}
void TextureExt :: unbind(int ind) {
	getFrame(ind)->unbind();
}


void TextureExt :: addFrame(string fileName) {
	addFrame(new Texture(fileName));
}
void TextureExt :: addFrame(Texture* tex) {
	frameList.push_back(tex);
}


Texture* TextureExt :: getFrame(int ind) {
	return frameList.at(ind % getFrameNumber());
}
Texture* TextureExt :: getFrame(float ind) {
	return frameList.at(mod(ind, getFrameNumber()));	
}


int TextureExt :: getWidth() {
	return getWidth(0);
}
int TextureExt :: getWidth(int frame) {
	return frameList.at(frame)->getWidth();
}
int TextureExt :: getHeight() {
	return getHeight(0);
}
int TextureExt :: getHeight(int frame) {
	return frameList.at(frame)->getHeight();
}


int TextureExt :: getFrameNumber() {
	return frameList.size();
}
