#pragma once

enum class EntityType
{
	Player,
	MeleeCharacter,
	RangedCharacter,
	misc

};

class CT_EntityData	: public CEntity
{
	
	virtual void Update(float deltaTime) = 0;

	EntityType entityType;



};