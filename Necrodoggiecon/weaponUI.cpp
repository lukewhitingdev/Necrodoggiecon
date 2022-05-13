#include "weaponUI.h"
#include <sstream>
#include "Cerberus/Core/Utility/Math/Math.h"

weaponUI::weaponUI()
{
	spriteBack = AddComponent<CSpriteComponent>();
	spriteBack->LoadTextureWIC("Resources\\uiBackground.png");
	spriteBack->SetRenderRect(XMUINT2(16, 16));
	spriteBack->SetSpriteSize(XMUINT2(70, 70));
	spriteBack->SetPosition(-600, -320, 1);
	spriteBack->SetScale(1,1,0);
	spriteBack->SetAnchor(XMFLOAT2(0, 1));
	spriteBack->translucency = true;
	spriteBack->material->material.Material.translucent = true;
	spriteBack->material->UpdateMaterial();

	ammoBack = AddComponent<CSpriteComponent>();
	ammoBack->LoadTextureWIC("Resources\\uiBackground.png");
	ammoBack->SetRenderRect(XMUINT2(16, 16));
	ammoBack->SetSpriteSize(XMUINT2(70, 70));
	ammoBack->SetPosition(-463, -320, 1);
	ammoBack->SetScale(3, 1, 0);
	ammoBack->SetAnchor(XMFLOAT2(0, 1));
	ammoBack->translucency = true;
	ammoBack->material->material.Material.translucent = true;
	ammoBack->material->UpdateMaterial();

	textWeaponName = AddComponent<CTextRenderComponent>();
	textWeaponName->SetJustification(TextJustification::Center);
	textWeaponName->SetFont("Resources\\fontBlack.png");
	textWeaponName->SetPosition(-462, -305, 0);
	textWeaponName->SetAnchor(XMFLOAT2(0, 1));
	textWeaponName->SetText("Magic Missile");
	
	textAmmoDisplay = AddComponent<CTextRenderComponent>();
	textAmmoDisplay->SetJustification(TextJustification::Center);
	textAmmoDisplay->SetFont("Resources\\fontBlack.png");
	textAmmoDisplay->SetPosition(-462, -335, 0);
	textAmmoDisplay->SetAnchor(XMFLOAT2(0, 1));
	textAmmoDisplay->SetText("69/420");
	
	weaponSprite = AddComponent<CSpriteComponent>();
	weaponSprite->LoadTextureWIC("Resources\\weapons\\Wand - Magic missile.png");
	weaponSprite->SetRenderRect(XMUINT2(64, 64));
	weaponSprite->SetSpriteSize(XMUINT2(64, 64));
	weaponSprite->SetPosition(-600, -318, 0);
	weaponSprite->SetScale(1,1,0);
	weaponSprite->SetAnchor(XMFLOAT2(0, 1));

	textTimer = AddComponent<CTextRenderComponent>();
	textTimer->SetJustification(TextJustification::Right);
	textTimer->SetReserveCount(12);
	textTimer->SetPosition(-628, 346, 0);
	textTimer->SetText("0:00.00");
	textTimer->SetAnchor(XMFLOAT2(0, 0));

	for (CComponent* e : components)
		e->ui = true;

	updateUI("Dagger", 0, 0, "Resources\\weapons\\Dagger.png");
}

//updateUI(std::string WeaponName, int currentAmmo, int maxAmmo, std::string spritePath)
void weaponUI::updateUI(std::string weaponName, int currentAmmo, int maxAmmo, std::string spritePath)
{
	textWeaponName->SetText(weaponName);
	textAmmoDisplay->SetText(std::to_string(currentAmmo) + "/" + std::to_string(maxAmmo));
	weaponSprite->LoadTextureWIC(spritePath);
}

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
