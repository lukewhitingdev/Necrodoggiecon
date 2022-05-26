/*****************************************************************//**
 * \file   GruntEnemy.cpp
 * \brief  All the functions needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "GruntEnemy.h"
#include "Cerberus/Core/Utility/IO.h"

GruntEnemy::GruntEnemy()
{
	sprite->LoadTextureWIC("Resources/Game/Characters/PurpleEnemySprite.png");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });

	weaponComponent = AddComponent<WeaponInterface>(NAME_OF(weaponComponent));
	weaponComponent->SetWeapon(new Crossbow());
	weaponComponent->SetUserType(USERTYPE::AI);

	weaponSprite = AddComponent<CSpriteComponent>(NAME_OF(weaponSprite));
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
void GruntEnemy::ChasePlayer(CCharacter* player)
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

static bool animating;
/**
 * Fire the weapon that it is holding.
 * 
 * \param player Player to attack.
 */
void GruntEnemy::AttackPlayer(CCharacter* player, float deltaTime)
{
	heading = Seek(player->GetPosition());

	// Impomptu Animation Code for weapons.
	Weapon* weapon = weaponComponent->GetCurrentWeapon();

	if (weapon->GetName() == "Dagger" || weapon->GetName() == "Rapier" || weapon->GetName() == "Longsword" && !animating)	// Positional based animations for melee.
	{
		if (weapon->GetCanFire())
		{
			weaponSprite->SetPosition(weaponSprite->GetPosition().x, weaponSprite->GetPosition().y + 10, weaponSprite->GetPosition().z);
			animating = true;
		}
	}

	weaponComponent->OnFire(aiPosition, velocity);
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	SetCurrentState(ChaseState::getInstance());
}

void GruntEnemy::Update(float deltaTime)
{

	Weapon* weapon = weaponComponent->GetCurrentWeapon();

	//Debug::Log("%d", weaponSprite->GetTextureOffset().x);

	// Set crossbow animation to empty bow when we cant fire or out of ammo.
	if (weapon->GetName() == "Crossbow")
	{
		if (!weapon->GetCanFire() || weapon->GetAmmo() <= 0)
		{
			weaponSprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
		}
		else
		{
			weaponSprite->SetTextureOffset(DirectX::XMFLOAT2(64, 0));
		}
	}

	// Reset melee animation if it has been triggered and we can fire again.
	if (weapon->GetCanFire() && animating)
	{
		weaponSprite->SetPosition(weaponSprite->GetPosition().x, weaponSprite->GetPosition().y - 10, weaponSprite->GetPosition().z);
		animating = false;
	}
	CAIController::Update(deltaTime);
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
