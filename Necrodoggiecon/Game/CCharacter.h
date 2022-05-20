#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "weapons.h"

class CCharacter : public CEntity
{
private:
protected:
	Weapon* weaponComponent = nullptr;
	/**
	* Virtual function
	* Called when the Character takes damage
	* Used for custom functionality on inherited classes
	*/
	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {
		UNREFERENCED_PARAMETER(damageCauser);
		UNREFERENCED_PARAMETER(damageAmount);
	};

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:
	/**
	* Public function used to apply damage to the character
	*/
	void ApplyDamage(float damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

	virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };

	CCharacter();
	virtual ~CCharacter();

};

