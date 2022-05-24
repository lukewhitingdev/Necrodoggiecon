#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "WeaponInterface.h"

class CCharacter : public CEntity
{
private:
protected:
	/**
	* Virtual function
	* Called when the Character takes damage
	* Used for custom functionality on inherited classes
	*/
	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {
		UNREFERENCED_PARAMETER(damageCauser);
		UNREFERENCED_PARAMETER(damageAmount);
	};
	float health = 2.0f;
	WeaponInterface* weaponComponent = nullptr;
	CSpriteComponent* weaponSprite = nullptr;

	void AddMovement(XMFLOAT2 vel, float deltaTime);
public:
	/**
	* Public function used to apply damage to the character
	*/
	void ApplyDamage(float damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

	virtual void Update(float deltaTime) {};

	CCharacter();
	virtual ~CCharacter();

	void EquipWeapon(Weapon* weapon);

	void UpdateWeaponSprite();

	void SetHealth(float heal);
	float GetHealth();
};

