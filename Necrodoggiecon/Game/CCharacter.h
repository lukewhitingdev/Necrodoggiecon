#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "weapons.h"

class CCharacter : public CEntity
{
private:
protected:
	Weapon* weaponComponent = nullptr;
	float health = 2.0f;

	void AddMovement(XMFLOAT2 vel, float deltaTime);
public:

	virtual void Update(float deltaTime) {};

	CCharacter();
	virtual ~CCharacter();

	void SetHealth(float heal);
	float GetHealth();
};

