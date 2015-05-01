// Character.h
// Ryan McGrail

#ifndef CHARACTER_H
#define CHARACTER_H

#include <deque>
#include "../Graphics/GraphicsOGL.h"
#include "../Primitives/Physical.h"
#include "../Graphics/Texture.h"

class GraphicsOGL;
class Character : public Physical {
	public:
		static SortedList<Character*> characterList;							// Static List of Characters
	
		Character(float, float, float);											// Constructor
		
		// Inherited 
		virtual void update(GraphicsOGL*, float);								// Updating
		virtual void draw(GraphicsOGL*, float);									// Drawing
		void drawStatWindow(GraphicsOGL*, float);								// Draw Stats

		virtual void destroy();													// Destroy Character 
		
		void faceDirection(float);												// Smoothly Rotate Shape to Direction
		void toolDirection(float);												// Smoothly Rotate Weapon to Direction

		void knockback(float);													// Knockback w/ Angle
		void knockback(float, float);											// Knockback w/ Speed, Angle
		virtual void damage(Character*,float);									// Taking Damage

		// Accessor/Mutator
		float getSize();														// Getting Size
		float getHP();															// Getting HP
		float getMaxHP();														// Getting MaxHP
		float getDestroyFraction();												// Get Destroy Animation Progress as Fraction	
		Character* getTarget();													// Get Current Target
		float getTargetShift();													// Get Target Window Fraction Onscreen

		static float GRAVITY_HOP_ACCELERATION;									// Hopping Gravity

	protected:
		virtual void attack();													// Attacking Trees/Characters
		virtual void land();													// Landing on Ground
		float calcDamage(float, Character* attacker, Character* defender);		// Calculate Damage Dealt by Attacker against Defender
		
		void collideCharacter();												// Collision w/ Another Character
		void collideTree();														// Collision w/ Tree

		void hop();																// Hop Once
		void updateHop(GraphicsOGL*, float);									// Update Hop Variables

		float size;																// Width of Character
		bool isHurt;															// Is Character Hurt?

		float knockbackDir;														// Knockback Variables
		float knockbackTimer;
																				// TARGET VARIABLES
		float targetTimer;														// Target Timer (Before Resetting)
		Character* target;														// Current Target
		float targetShift;														// Target Shift (How Much Stat Window Should Come Out)

		float faceDir;															// Shape Direction
		float toolDir;															// Weapon Direction
		
		float hopZ;																// Hopping Variables
		float hopZVel;
		float hopX;
		float hopSc;
		float hopDir;
	
		bool isMoving;															// Is Character Currently Moving Along XY?
		
		float attackTimer;														// Attack Timer (Before Character can Attack Again)

		int shape;																// Shape Type
		float appearanceR;														// Shape Color (R)
		float appearanceG;														// Shape Color (G)
		float appearanceB;														// Shape Color (B)
		float appearanceXScale;													// Shape X Scale
		float appearanceYScale;													// Shape Y Scale
		float appearanceZScale;													// Shape Z Scale

		float destroyTimer;														// Destroy Variables
		float destroyToX;
		float destroyToY;
		float destroyToZ;
		float destroyShrTimer;

		float wXRot;															// Weapon XYZ Rotation
		float wYRot;
		float wZRot;

		// STATS
			int level;															// Level
			float hp;															// Health Points
			float maxHP;														// Maximum Health Points
			float atk;															// Attack Strength
			float def;															// Defense Strength


	private:
		Texture* swordHiltTex;													// Sword Hilt Texture
};

#endif
