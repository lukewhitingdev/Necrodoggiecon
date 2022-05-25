#include "CCharacter.h"
#include "Necrodoggiecon\Game\WeaponPickup.h"

/*****************************************************************//**
 * \file   CCharacter.cpp
 * \brief  Base class for Characters
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/

CCharacter::CCharacter()
{
	
}

CCharacter::~CCharacter()
{
	if (weaponComponent != nullptr)
	{
		WeaponPickup<Weapon>* pickup = Engine::CreateEntity<WeaponPickup<Weapon>>();
		pickup->SetWeapon(weaponComponent->GetCurrentWeapon());
		pickup->SetPosition(this->GetPosition());
	}
}


void CCharacter::EquipWeapon(Weapon* weapon)
{
	weaponComponent->SetWeapon(weapon);
	UpdateWeaponSprite();
}

void CCharacter::UpdateWeaponSprite()
{
	HRESULT hr;
	if (IO::FindExtension(weaponComponent->GetCurrentWeapon()->GetIconPath()) == "dds")
	{
		hr = weaponSprite->LoadTexture(weaponComponent->GetCurrentWeapon()->GetIconPath());
		if (FAILED(hr))
		{
			Debug::LogHResult(hr, "Weapon Tried to load texture using path: %s but the loader returned failure.", weaponComponent->GetCurrentWeapon()->GetIconPath().c_str());
			return;
		}
	}
	else
	{
		hr = weaponSprite->LoadTextureWIC(weaponComponent->GetCurrentWeapon()->GetIconPath());
		if (FAILED(hr))
		{
			Debug::LogHResult(hr, "Weapon Tried to load texture using path: %s but the loader returned failure.", weaponComponent->GetCurrentWeapon()->GetIconPath().c_str());
			return;
		}
	}


	
}

void CCharacter::SetHealth(float heal)
{
	health = heal;
}

float CCharacter::GetHealth()
{
	return health;
}

void CCharacter::UpdateWeaponSpritePosition(CSpriteComponent* wSprite)
{
	weaponSprite->SetPosition(Vector3(wSprite->GetSpriteSize().y / 2, -int(wSprite->GetSpriteSize().x - 40), 0));
	weaponSprite->SetRotation(-1.5708); // 90 Degrees in radians.
}

void CCharacter::AddMovement(XMFLOAT2 vel, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += vel.x * deltaTime;
	pos.y += vel.y * deltaTime;
	SetPosition(pos);
}
