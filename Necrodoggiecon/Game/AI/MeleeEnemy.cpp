/*****************************************************************//**
 * \file   MeleeEnemy.cpp
 * \brief  All the functions needed to control the Melee Enemies.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	sprite->LoadTexture("Resources\\MeleeEnemy.dds");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });

	weapon = new Weapon();
	weapon->SetUserType(USERTYPE::AI);
	
}

void MeleeEnemy::ChasePlayer(CCharacter* player)
{
	if (aiPosition.DistanceTo(player->GetPosition()) < weapon->GetRange())
	{
		SetCurrentState(AttackState::getInstance());
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

void MeleeEnemy::AttackPlayer(CCharacter* player)
{
	weapon->OnFire(aiPosition, heading);
	players = Engine::GetEntityOfType<PlayerCharacter>();
}
