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

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:

	virtual void Update(float deltaTime) {};

	CCharacter();
	virtual ~CCharacter();

	void SetHealth(float heal);
	float GetHealth();
};

