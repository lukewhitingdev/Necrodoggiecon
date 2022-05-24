/*****************************************************************//**
 * \file   GruntEnemy.cpp
 * \brief  All the functions needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "GruntEnemy.h"
#include "Cerberus/Core/Utility/IO.h"
#include <Necrodoggiecon/Weapons/Ranged/Fireball.h>

GruntEnemy::GruntEnemy()
{
	sprite->LoadTexture("Resources/Game/Characters/MeleeEnemy.dds");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });

	weaponComponent = AddComponent<WeaponInterface>();
	weaponComponent->SetWeapon(new Crossbow());
	weaponComponent->SetUserType(USERTYPE::AI);

	weaponSprite = AddComponent<CSpriteComponent>();
	UpdateWeaponSprite();
	weaponSprite->SetPosition(Vector3(sprite->GetSpriteSize().y / 2, int(sprite->GetSpriteSize().x - 20), 0));
	weaponSprite->SetRotation(0); // 90 Degrees in radians.
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	weaponSprite->SetRenderRect(weaponComponent->GetCurrentWeapon()->GetRenderRect());
	weaponSprite->SetScale(weaponComponent->GetCurrentWeapon()->GetScale());
}

/**
 * Seek towards the player and if in range go to the attack state.
 * 
 * \param player
 */
void GruntEnemy::ChasePlayer(PlayerCharacter* player)
{
	
	if (aiPosition.DistanceTo(player->GetPosition()) < weaponComponent->GetCurrentWeapon()->GetRange())
	{
		SetCurrentState(AttackState::getInstance());
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

/**
 * Fire the weapon that it is holding.
 * 
 * \param player Player to attack.
 */
void GruntEnemy::AttackPlayer(PlayerCharacter* player, float deltaTime)
{
	weaponComponent->OnFire(aiPosition, velocity);
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	SetCurrentState(ChaseState::getInstance());
}

void GruntEnemy::UpdateWeaponSprite()
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
