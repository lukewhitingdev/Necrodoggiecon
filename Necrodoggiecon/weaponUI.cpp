#include "weaponUI.h"


weaponUI::weaponUI()
{
	spriteBack = AddComponent<CSpriteComponent>();
	spriteBack->LoadTextureWIC("Resources\\uiBackground.png");
	spriteBack->SetRenderRect(XMUINT2(16, 16));
	spriteBack->SetSpriteSize(XMUINT2(70, 70));
	spriteBack->SetPosition(-600, -320, 1);
	spriteBack->SetScale(1,1,0);
	spriteBack->SetAnchor(XMFLOAT2(0, 1));

	ammoBack = AddComponent<CSpriteComponent>();
	ammoBack->LoadTextureWIC("Resources\\uiBackground.png");
	ammoBack->SetRenderRect(XMUINT2(16, 16));
	ammoBack->SetSpriteSize(XMUINT2(70, 70));
	ammoBack->SetPosition(-463, -320, 1);
	ammoBack->SetScale(3, 1, 0);
	ammoBack->SetAnchor(XMFLOAT2(0, 1));

	textWeaponName = AddComponent<CTextRenderComponent>();
	textWeaponName->SetJustification(TextJustification::Right);
	textWeaponName->SetFont("Resources\\fontBlack.png");
	textWeaponName->SetPosition(-546, -305, 0);
	textWeaponName->SetAnchor(XMFLOAT2(0, 1));
	textWeaponName->SetText("Magic Missile");
	
	textAmmoDisplay = AddComponent<CTextRenderComponent>();
	textAmmoDisplay->SetJustification(TextJustification::Center);
	textAmmoDisplay->SetFont("Resources\\fontBlack.png");
	textAmmoDisplay->SetPosition(-466, -335, 0);
	textAmmoDisplay->SetAnchor(XMFLOAT2(0, 1));
	textAmmoDisplay->SetText("69/420");
	
	weaponSprite = AddComponent<CSpriteComponent>();
	weaponSprite->LoadTextureWIC("Resources\\weapons\\Sword.png");
	weaponSprite->SetRenderRect(XMUINT2(64, 64));
	weaponSprite->SetSpriteSize(XMUINT2(64, 64));
	weaponSprite->SetPosition(-600, -318, 0);
	weaponSprite->SetScale(1,1,0);
	weaponSprite->SetAnchor(XMFLOAT2(0, 1));

	for (CComponent* e : components)
		e->ui = true;
}

void weaponUI::updateUI()
{

}

weaponUI::~weaponUI()
{
}
