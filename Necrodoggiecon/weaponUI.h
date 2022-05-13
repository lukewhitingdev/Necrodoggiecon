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
	class CTextRenderComponent* textTimer = nullptr;

	float seconds = 0;
	int minutes = 0;

public:
	weaponUI();
	virtual void updateUI(std::string WeaponName, int currentAmmo, int maxAmmo, std::string spritePath);
	virtual void Update(float deltaTime) override;
	virtual ~weaponUI();
};