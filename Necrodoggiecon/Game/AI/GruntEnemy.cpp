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

	weapon = new WeaponInterface(); //Needs to be component
	weapon->SetUserType(USERTYPE::AI);
	weapon->SetWeapon(new Dagger()); //Needs to be a crossbow
	
	weaponComponent = AddComponent<Weapon>();
	weaponComponent->SetWeapon("Crossbow");
	weaponComponent->SetUserType(USERTYPE::AI);
	
}

/**
 * Seek towards the player and if in range go to the attack state.
 * 
 * \param player
 */
void GruntEnemy::ChasePlayer(PlayerCharacter* player)
{
	
	if (aiPosition.DistanceTo(player->GetPosition()) < weapon->GetCurrentWeapon()->GetRange())
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
	SetCurrentState(ChaseState::getInstance());
}
