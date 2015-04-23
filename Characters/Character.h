// Character.h


#ifndef CHARACTER_H
#define CHARACTER_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "../Graphics/Texture.h"

class GraphicsOGL;
class Character : public Physical {
	public:
		static SortedList<Character*> characterList;				// Static List of Characters
	
		Character(float, float, float);								// Constructor
		
		// Inherited 
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		virtual void destroy();										// 

		
		void faceDirection(float);
		void toolDirection(float);

		// Knock Back
		void knockback(float);
		void knockback(float, float);

		// Take Damage
		virtual void damage(Character*,float);			

		static float GRAVITY_HOP_ACCELERATION;						// Hopping Gravity

		// Accessor/Mutator
		float getSize();
		float getHP();
		float getMaxHP();
		float getDestroyFraction();
		float getTarget();
		float getTargetShift();

		void drawStatWindow(GraphicsOGL*, float);

	protected:
		virtual void attack();
		virtual void land();
		float calcDamage(float, Character* attacker, Character* defender);		// Calculate Damage Dealt by Attacker against Defender
		
		void collideCharacter();
		void collideTree();

		
		void hop();
		void updateHop(GraphicsOGL*, float);

		float size;
		bool isHurt;
		float knockbackDir;
		float knockbackTimer;

																				// TARGET VARIABLES
		float targetTimer;														// Target Timer (Before Resetting)
		Character* target;														// Current Target
		float targetShift;														// Target Shift (How Much Stat Window Should Come Out)

		
		float faceDir;
		float toolDir;
		float hopZ;
		float hopZVel;
		float hopX;
		float hopSc;
		float hopDir;
		bool isMoving;
		float attackTimer;

		int shape;																// Shape Type
		float appearanceR;														// Shape Color (R)
		float appearanceG;														// Shape Color (G)
		float appearanceB;														// Shape Color (B)
		float appearanceXScale;													// Shape X Scale
		float appearanceYScale;													// Shape Y Scale
		float appearanceZScale;													// Shape Z Scale

		float destroyTimer;
		float destroyToX;
		float destroyToY;
		float destroyToZ;
		float destroyShrTimer;


		float wXRot;
		float wYRot;
		float wZRot;

		// STATS
			int level;															// Level
			float hp;															// Health Points
			float maxHP;														// Maximum Health Points
			float atk;															// Attack Strength
			float def;															// Defense Strength


	private:
		
		Texture* swordHiltTex;
};

#endif
