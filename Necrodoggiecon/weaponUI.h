#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Components\CTextRenderComponent.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Structs\CCamera.h"

class weaponUI : public CEntity
{
	class CSpriteComponent* spriteBack = nullptr;
	class CSpriteComponent* ammoBack = nullptr;
	class CSpriteComponent* weaponSprite = nullptr;
	class CTextRenderComponent* textWeaponName = nullptr;
	class CTextRenderComponent* textAmmoDisplay = nullptr;

	int currentAmmo = 0;
	int maxAmmo = 0;
	std::string weaponName = "null";

public:
	weaponUI();
	virtual void updateUI();
	virtual void Update(float deltaTime) override {};
	virtual ~weaponUI();
};