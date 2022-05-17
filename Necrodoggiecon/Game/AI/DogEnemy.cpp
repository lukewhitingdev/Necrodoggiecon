#include "DogEnemy.h"

DogEnemy::DogEnemy()
{
	sprite->LoadTexture("Resources\\MeleeEnemy.dds");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });
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

void DogEnemy::AttackPlayer(CCharacter* player)
{
	if (!onCooldown)
		SetSpeed(1.0f);
		
	heading = Seek(player->GetPosition());

	if (attackCooldown > 0.0f)
	{
		attackCooldown -= 0.016f;
		SetSpeed(500.0f);
		onCooldown = true;

		// If the timer is up then go back to pathfinding.
		if (attackCooldown < 0.02f)
		{
			onCooldown = false;
			attackCooldown = 1.0f;
		}
			
	}

}
