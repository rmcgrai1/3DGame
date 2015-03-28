// Sign.h

#ifndef SIGN_H
#define SIGN_H

#include "../GraphicsOGL.h"
#include <string>

class Sign : public Environmental {
	public:
		Sign(float x, float y, float z, string text);
		void update(GraphicsOGL*, float);
		void draw(GraphicsOGL*, float);
		
	private:
		string text;
		bool isDisplaying;
};

#endif