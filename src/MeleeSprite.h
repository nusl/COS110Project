#ifndef MELEE_SPRITE_H
#define MELEE_SPRITE_H

#include "Sprite.h"

class MeleeSprite : public Sprite
{
	public:
		MeleeSprite
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		//,unsigned int inRange
		,unsigned int inAttackPower
		,unsigned int inMoveRange
		,double inHitChance
		,double inCritChance
		,double inDodgeChance
		,double inParryChance
		,char inState
		,char inType
		//,bool inMoveOnto
		,double inRegenRate
		,double inRegenCounter
		):
		Sprite
		(inMaxLife
		,inCurrentLife
		,inMoveCount
		,1//inRange
		,inAttackPower
		,inMoveRange
		,inHitChance
		,inCritChance
		,inDodgeChance
		,inParryChance
		,inState
		,inType
		//,false//inMoveOnto
		,inRegenRate
		,inRegenCounter
		)
		{}
};

#endif
