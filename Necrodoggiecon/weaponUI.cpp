/*****************************************************************//**
 * \file   weaponUI.cpp
 * \brief  This is the CPP for the weapon UI and the timer
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#include "weaponUI.h"
#include <sstream>
#include "Cerberus/Core/Utility/Math/Math.h"
#include "Cerberus\Core\Components\CTextRenderComponent.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Structs\CCamera.h"

/**
 * Sets up all of the UI elements.
 * 
 */
weaponUI::weaponUI()
{
	spriteBack = AddComponent<CSpriteComponent>();
	spriteBack->LoadTextureWIC("Resources/Game/uiBackground.png");
	spriteBack->SetRenderRect(XMUINT2(16, 16));
	spriteBack->SetSpriteSize(XMUINT2(70, 70));
	spriteBack->SetPosition(-600, -320, 0);
	spriteBack->SetAnchor(XMFLOAT2(0, 1));
	//spriteBack->SetUseTranslucency(true);
	//spriteBack->SetTint(XMFLOAT4(0, 0, 0, -0.3f));

	ammoBack = AddComponent<CSpriteComponent>();
	ammoBack->LoadTextureWIC("Resources/Game/uiBackground.png");
	ammoBack->SetRenderRect(XMUINT2(16, 16));
	ammoBack->SetSpriteSize(XMUINT2(70, 70));
	ammoBack->SetPosition(-463, -320, 1);
	ammoBack->SetScale(3, 1, 0);
	ammoBack->SetAnchor(XMFLOAT2(0, 1));
	//ammoBack->SetUseTranslucency(true);
	//ammoBack->SetTint(XMFLOAT4(0, 0, 0, -0.3f));

	textWeaponName = AddComponent<CTextRenderComponent>();
	textWeaponName->SetJustification(TextJustification::Center);
	textWeaponName->SetFont("Resources/Engine/fontBlack.png");
	textWeaponName->SetPosition(-462, -305, 0);
	textWeaponName->SetAnchor(XMFLOAT2(0, 1));
	textWeaponName->SetText("Magic Missile");
	
	textAmmoDisplay = AddComponent<CTextRenderComponent>();
	textAmmoDisplay->SetJustification(TextJustification::Center);
	textAmmoDisplay->SetFont("Resources/Engine/fontBlack.png");
	textAmmoDisplay->SetPosition(-462, -335, 0);
	textAmmoDisplay->SetAnchor(XMFLOAT2(0, 1));
	textAmmoDisplay->SetText("69/420");
	
	weaponSprite = AddComponent<CSpriteComponent>();
	weaponSprite->LoadTextureWIC("Resources/Game/weapons/Wand - Magic missile.png");
	weaponSprite->SetRenderRect(XMUINT2(64, 64));
	weaponSprite->SetSpriteSize(XMUINT2(64, 64));
	weaponSprite->SetPosition(-600, -318, -1);
	weaponSprite->SetScale(1,1,0);
	weaponSprite->SetAnchor(XMFLOAT2(0, 1));

	textTimer = AddComponent<CTextRenderComponent>();
	textTimer->SetJustification(TextJustification::Right);
	textTimer->SetReserveCount(12);
	textTimer->SetPosition(-628, 346, -1);
	textTimer->SetText("0:00.00");
	textTimer->SetAnchor(XMFLOAT2(0, 0));

	for (CComponent* e : GetAllComponents())
		e->SetIsUI(true);

	updateUI("Dagger", 0, 0, "Resources/Game/weapons/Dagger.png");
}

/**
 * Updates Weapon UI elements when called ideally after a change is made.
 * 
 * \param weaponName
 * \param currentAmmo
 * \param maxAmmo
 * \param spritePath
 */
void weaponUI::updateUI(std::string weaponName, int currentAmmo, int maxAmmo, std::string spritePath)
{
	textWeaponName->SetText(weaponName);
	textAmmoDisplay->SetText(std::to_string(currentAmmo) + "/" + std::to_string(maxAmmo));
	weaponSprite->LoadTextureWIC(spritePath);
}

/**
 * Updates timer each frame.
 * 
 * \param deltaTime
 */
void weaponUI::Update(float deltaTime)
{
	seconds += deltaTime;
	if (seconds >= 60)
	{
		minutes += 1;
		seconds -= 60;
	}

	std::stringstream ss;
	ss << Math::IntToString(minutes, 2) << ":" << Math::FloatToStringWithDigits(seconds, 2, true, 2);
	textTimer->SetText(ss.str());
}

weaponUI::~weaponUI()
{
}
