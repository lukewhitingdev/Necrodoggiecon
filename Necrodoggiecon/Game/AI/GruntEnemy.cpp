/*****************************************************************//**
 * \file   GruntEnemy.cpp
 * \brief  All the functions needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "GruntEnemy.h"

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

	attackAudioEmitter = AddComponent<CAudioEmitterComponent>();
	attackAudioEmitter->Load(weaponComponent->GetCurrentWeapon()->GetAttackSoundPath());
	attackAudioEmitter->SetRange(0.0f);

	deathAudioEmitter = AddComponent<CAudioEmitterComponent>();
	deathAudioEmitter->Load("Resources/Game/Audio/DeathSound.wav");
	deathAudioEmitter->SetRange(0.0f);
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
	if (weaponComponent->OnFire(aiPosition, velocity))
		attackAudioEmitter->Play();

	SetCurrentState(ChaseState::getInstance());
}
void GruntEnemy::OnDeath()
{
	deathAudioEmitter->Play();
}
