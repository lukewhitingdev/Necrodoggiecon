#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "weapons.h"

class CCharacter : public CEntity
{
private:
protected:
	Weapon* weaponComponent = nullptr;

	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {
		UNREFERENCED_PARAMETER(damageCauser);
		UNREFERENCED_PARAMETER(damageAmount);
	};

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:
	void ApplyDamage(float damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

	virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };

	CCharacter();
	virtual ~CCharacter();

};

