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
}

void MeleeEnemy::Update(float deltaTime)
{
	// Set the local variable for the AI position.
	aiPosition = GetPosition();

	// Run the finite state machine
	currentState->Update(this);

	CheckForPlayer();

	MoveViewFrustrum();

	// If the AI is not pathfinding or searching then check for collisions with obstacles.
	if (currentState != &PatrolState::getInstance() && currentState != &SearchState::getInstance())
		heading += CollisionAvoidance();

	// Move the AI if it is not lost
	if (currentState != &SearchState::getInstance())
		Movement(deltaTime);

	// Make sure the AI is on a 2D vector.
	aiPosition.z = 0.0f;

	// Set the position of the entity to the local variable for the AI position.
	SetPosition(aiPosition);
}

void MeleeEnemy::ChasePlayer(PlayerCharacter* player)
{
	if (aiPosition.DistanceTo(player->GetPosition()) < 10.0f)
	{
		SetCurrentState(AttackState::getInstance());
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

void MeleeEnemy::AttackPlayer(PlayerCharacter* player)
{
}

void MeleeEnemy::GetIntoCover()
{
}
