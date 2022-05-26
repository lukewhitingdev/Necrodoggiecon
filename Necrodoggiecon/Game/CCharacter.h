#pragma once
#include <Cerberus\Core\Components\CAnimationSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>
#include "WeaponInterface.h"

class CCharacter : public CEntity
{
private:
protected:
	bool isPlayer = false;
	bool visible = true;
	float health = 1.0f;
	WeaponInterface* weaponComponent = nullptr;
	CSpriteComponent* weaponSprite = nullptr;

	void UpdateWeaponSpritePosition(CSpriteComponent* wSprite);

	void AddMovement(XMFLOAT2 vel, float deltaTime);

	
public:
	/**
	* Public function used to apply damage to the character
	*/
	virtual void ApplyDamage(float damageAmount) {};

	virtual void Update(float deltaTime) {};

	CCharacter();
	virtual ~CCharacter();

	void EquipWeapon(Weapon* weapon);

	void UpdateWeaponSprite();

	void SetHealth(float heal);
	float GetHealth();
	
	void SetIsPlayer(bool player);
	bool GetIsPlayer();

	bool GetVisible() { return visible; }
};

