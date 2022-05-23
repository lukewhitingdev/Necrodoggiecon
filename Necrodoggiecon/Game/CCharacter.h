#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "WeaponInterface.h"

class CCharacter : public CEntity
{
private:
protected:
	WeaponInterface* weaponComponent = nullptr;
	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {
		UNREFERENCED_PARAMETER(damageCauser);
		UNREFERENCED_PARAMETER(damageAmount);
	};
	float health = 2.0f;

	void AddMovement(XMFLOAT2 vel, float deltaTime);
public:

	virtual void Update(float deltaTime) {};

	CCharacter();
	virtual ~CCharacter();

	void SetHealth(float heal);
	float GetHealth();
};

