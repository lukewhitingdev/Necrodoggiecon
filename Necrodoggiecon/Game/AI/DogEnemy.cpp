#include "DogEnemy.h"

DogEnemy::DogEnemy()
{
	sprite->LoadTexture("Resources\\MeleeEnemy.dds");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });
}

void DogEnemy::Update(float deltaTime)
{
	if (attackCooldown > 0.0f)
	{
		attackCooldown -= 0.016f;
		isAttacking = false;
		// If the timer is up then go back to pathfinding.
		if (attackCooldown < 0.02f)
		{
			attackTimer = 0.5f;
			onCooldown = false;
		}

	}


	CAIController::Update(deltaTime);
}

void DogEnemy::ChasePlayer(CCharacter* player)
{
	if (aiPosition.DistanceTo(player->GetPosition()) < attackRange)
	{
		SetCurrentState(AttackState::getInstance());
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

void DogEnemy::AttackEnter(CCharacter* player)
{
	targetPosition = player->GetPosition();
}

void DogEnemy::AttackPlayer(CCharacter* player)
{
		
	heading = Seek(targetPosition);

	if (attackTimer > 0.0f && !onCooldown)
	{
		attackTimer -= 0.016f;
		SetSpeed(1.0f);
		if (attackTimer <= 0.3f)
			SetSpeed(500.0f);
		onCooldown = false;
		isAttacking = true;

		// If the timer is up then go back to pathfinding.
		if (attackTimer < 0.02f)
		{
			onCooldown = true;
			attackTimer = 0.5f;
			attackCooldown = 20.0f;
		}
			
	}

}
