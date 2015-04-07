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
		Character(float, float, float);
		virtual void update(GraphicsOGL*, float);
		virtual void draw(GraphicsOGL*, float);
		void knockback(float kDir);
		void faceDirection(float);
		void toolDirection(float);

		virtual void damage(Character*,float);
		virtual void destroy();

		static float GRAVITY_HOP_ACCELERATION;

		static SortedList<Character*> characterList;

		float getHP();
		float getMaxHP();
		float getTarget();
		float getTargetShift();

		void drawStatWindow(GraphicsOGL*, float);

		Character* target;
		float targetShift;

	protected:
		virtual void attack();
		virtual void land();
		void hop();

		float knockbackDir;
		float knockbackTimer;

		float targetTimer;

		float faceDir;
		float toolDir;
		float hopZ;
		float hopZVel;
		float hopX;	
		bool isMoving;
		float attackTimer;

		float wXRot;
		float wYRot;
		float wZRot;

		// STATS
			int level;
			float hp;
			float maxHP;
			float atk;
			float def;

		int shape;

		float calcDamage(float, Character*, Character*);

	private:
		void updateHop(float);
		void collideCharacter();
		void collideTree();
		
		float hopSc;
		float hopDir;
		
		static Texture* shTex;
};

#endif
