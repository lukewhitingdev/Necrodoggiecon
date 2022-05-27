/*****************************************************************//**
 * \file   DogEnemy.cpp
 * \brief  File containing all the functions needed for the dog enemy.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "DogEnemy.h"
#include "Game/SoundManager.h"

DogEnemy::DogEnemy()
{
	sprite->LoadTextureWIC("Resources/Game/Characters/DogSpriteFinal.png");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });
	sprite->SetAnimationRectSize(XMUINT2(1, 7));
	sprite->SetAnimationSpeed(walkAnimationSpeed);
	sprite->SetPlaying(false, false);
}

void DogEnemy::Update(float deltaTime)
{
	if (attackCooldown > 0.0f)
	{
		attackCooldown -= deltaTime;
		isAttacking = false;
		// If the timer is up then go back to pathfinding.
		if (attackCooldown < 0.02f)
		{
			attackTimer = 1.0f;
			onCooldown = false;
			targetPosition = players[0]->GetPosition();
		}

	}
	if (sprite->GetPlaying() == false && velocity.Magnitude() != 0.0f)
	{
		sprite->SetPlaying(true, false);
	}

	CAIController::Update(deltaTime);
}

/**
 * Seek towards the player and switch to attacking once in range.
 * 
 * \param player Player to seek towards.
 */
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

/**
 * Get the target position to dash towards.
 * 
 * \param player Player to target for an attack.
 */
void DogEnemy::AttackEnter(CCharacter* player)
{
	targetPosition = player->GetPosition();
}

/**
 * If not on cooldown then charge up a dash attack and then dash at the target position.
 * 
 * \param player Player to attack.
 */
void DogEnemy::AttackPlayer(CCharacter* player, float deltaTime)
{
		
	heading = Seek(targetPosition);

	if (attackTimer > 0.0f && !onCooldown)
	{
		attackTimer -= deltaTime;
		SetSpeed(1.0f);
		if (attackTimer <= 0.6f)
			SetSpeed(500.0f);
		onCooldown = false;
		isAttacking = true;

		if (aiPosition.DistanceTo(player->GetPosition()) < 10.0f)
		{
			player->ApplyDamage(1.0f);
			SoundManager::PlaySound("DogBark", GetPosition());

			onCooldown = true;
			attackTimer = 1.0f;
			attackCooldown = 20.0f;
			SetCurrentState(ChaseState::getInstance());
		}
			

		// If the timer is up then go back to pathfinding.
		if (attackTimer < 0.02f)
		{
			onCooldown = true;
			attackTimer = 1.0f;
			attackCooldown = 20.0f;
			SetCurrentState(ChaseState::getInstance());
		}
			
	}
	else
	{
		heading = Seek(player->GetPosition());
	}

}
void DogEnemy::OnDeath()
{
	SoundManager::PlaySound("DeathSound", GetPosition());
}

void DogEnemy::OnHit(const std::string& hitSound)
{
	SoundManager::PlaySound(hitSound, GetPosition());
}