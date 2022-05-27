/*****************************************************************//**
 * \file   GruntEnemy.cpp
 * \brief  All the functions needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "GruntEnemy.h"
#include "Game/SoundManager.h"
#include "Cerberus/Core/Utility/IO.h"
#include "Necrodoggiecon/Weapons/Melee/Dagger.h"
GruntEnemy::GruntEnemy()
{
	sprite->LoadTextureWIC("Resources/Game/Characters/RedEnemySprite.png");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });
	sprite->SetAnimationRectSize(XMUINT2(1, 1));
	sprite->SetAnimationRectPosition(XMUINT2(0, 0));
	sprite->SetPlaying(true, false);

	weaponComponent = AddComponent<WeaponInterface>(NAME_OF(weaponComponent));
	weaponComponent->SetWeapon(new Dagger());
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
	

	Weapon* weapon = weaponComponent->GetCurrentWeapon();
	if (weapon->GetName() == "Crossbow")	// Crossbow exclusive animations, can be extended to include any animations that are 2 cycle.
	{
		if (weapon->GetCanFire())
		{
			weaponSprite->SetTextureOffset(DirectX::XMFLOAT2(0, 0));
		}

	}
	else if (weapon->GetName() == "Dagger" || weapon->GetName() == "Rapier" || weapon->GetName() == "Longsword" && !animating)	// Positional based animations for melee.
	{
		if (weapon->GetCanFire())
		{
			weaponSprite->SetPosition(weaponSprite->GetPosition().x + 10, weaponSprite->GetPosition().y, weaponSprite->GetPosition().z);
			animating = true;
		}
	}

	if (weapon->GetCanFire())
	{
		if(weaponComponent->OnFire(GetPosition(), velocity.Normalize()))
			SoundManager::PlaySound(weaponComponent->GetCurrentWeapon()->GetAttackSound(), GetPosition());
	}
	SetCurrentState(ChaseState::getInstance());
}

void GruntEnemy::OnDeath()
{
	SoundManager::PlaySound("DeathSound", GetPosition());
}
void GruntEnemy::OnHit(const std::string& hitSound)
{
	SoundManager::PlaySound(hitSound, GetPosition());
}
void GruntEnemy::Update(float deltaTime)
{
	Weapon* weapon = weaponComponent->GetCurrentWeapon();

	// Set crossbow animation to empty bow when we cant fire or out of ammo.
	if (weapon->GetName() == "Crossbow")
	{
		if (!weapon->GetCanFire() || weapon->GetAmmo() <= 0)
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
	weaponComponent->Update(deltaTime);
	weaponSprite->SetTextureOffset(weaponComponent->GetCurrentWeapon()->GetTextureOffset());
	weaponSprite->SetRenderRect(weaponComponent->GetCurrentWeapon()->GetRenderRect());
	weaponSprite->SetScale(weaponComponent->GetCurrentWeapon()->GetScale());


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
