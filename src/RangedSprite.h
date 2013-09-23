#ifndef RANGED_SPRITE_H
#define RANGED_SPRITE_H

#include "Sprite.h"

class RangedSprite : public Sprite
{
	public:
		RangedSprite
		(unsigned int inMaxLife
		,unsigned int inCurrentLife
		,unsigned int inMoveCount
		//,unsigned int inRange
		,unsigned int inAttackPower
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
		,2//inRange
		,inAttackPower
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
