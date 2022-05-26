/*****************************************************************//**
 * \file   HomingProjectile.cpp
 * \brief  All the functions needed for Homing Projectile.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "HomingProjectile.h"
#include "Necrodoggiecon\Game\AI\CAIController.h"
#include "Necrodoggiecon/Game/PlayerCharacter.h"

HomingProjectile::HomingProjectile()
{
}

HomingProjectile::~HomingProjectile()
{
}


/**
 * Will make a projectile that will home into a enemy
 *
 * \Homes and then Damages the target if it hit
 */
void HomingProjectile::Update(float deltaTime)
{
	if (Projectile::GetLifetime() > 0)
	{
		if (Projectile::GetUserType() == USERTYPE2::PLAYER)
		{
			DidItHit();
			CAIController* target = GetClosestEnemy(Projectile::GetPosition(), 50000);
			if (target != nullptr)
			{
				Vector3 attack = target->GetPosition() - Projectile::GetPosition();
				Projectile::SetPosition(Projectile::GetPosition() + (attack * Projectile::GetSpeed()) * deltaTime);
				ProjectileSprite->SetPosition(Projectile::GetPosition());
				Projectile::GetLifetime() - 2;
			}
			else
			{
				Projectile::SetPosition(Projectile::GetPosition() + Projectile::GetDirection() * Projectile::GetSpeed());
				ProjectileSprite->SetPosition(Projectile::GetPosition());
			}
		}
		else if (Projectile::GetUserType() == USERTYPE2::AI)
		{
			DidItHit();
			CCharacter* target = GetClosestPlayer(Projectile::GetPosition(), 50000);
			if (target != nullptr)
			{
				Vector3 attack = target->GetPosition() - Projectile::GetPosition();
				Projectile::SetPosition(Projectile::GetPosition() + (attack * Projectile::GetSpeed()) * deltaTime);
				ProjectileSprite->SetPosition(Projectile::GetPosition());
				Projectile::GetLifetime() - 2;
			}
			else
			{
				Projectile::SetPosition(Projectile::GetPosition() + Projectile::GetDirection() * Projectile::GetSpeed());
				ProjectileSprite->SetPosition(Projectile::GetPosition());
			}
		}
	}
	else
		Engine::DestroyEntity(this);
}

/**
 * Gets the closest enemy to the player within a given range.
 * 
 * \param actorPos
 * \param ranged
 * \return CAIController of closest enemy to the player within a given range
 */
CAIController* HomingProjectile::GetClosestEnemy(Vector3 actorPos, float ranged)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > ranged)
			continue;

		if (closestEnemy == nullptr)
			closestEnemy = enemy;
		else
		{
			if (actorPos.DistanceTo(enemy->GetPosition()) < actorPos.DistanceTo(closestEnemy->GetPosition()))
				closestEnemy = enemy;
		}
	}

	return closestEnemy;
}

/**
 * Gets the closest player to the enemy within a given range.
 * 
 * \param actorPos
 * \param ranged
 * \return CCharacter of closest player to the enemy withion the given range
 */
CCharacter* HomingProjectile::GetClosestPlayer(Vector3 actorPos, float ranged)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No enemies
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each enemy
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > ranged)
			continue;

		if (closestPlayer == nullptr)
			closestPlayer = player;
		else
		{
			if (actorPos.DistanceTo(player->GetPosition()) < actorPos.DistanceTo(closestPlayer->GetPosition()))
				closestPlayer = player;
		}
	}

	return closestPlayer;
}
