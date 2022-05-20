/*****************************************************************//**
 * \file   Projectile.cpp
 * \brief  All the functions needed for the Projectile.
 * 
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "Projectile.h"
#include <Necrodoggiecon\Game\AI\CAIController.h>

Projectile::Projectile()
{
	ProjectileSprite = AddComponent<CSpriteComponent>();
	ProjectileSprite->SetRenderRect(XMUINT2(64, 64));
	ProjectileSprite->SetSpriteSize(XMUINT2(64, 64));
}


Projectile::~Projectile()
{

}

/**
 * .
 *
 * \param deltaTime
 */
void Projectile::Update(float deltaTime)
{
	if (Lifetime > 0)
	{
		DidItHit();
		Position += Direction * Speed;
		ProjectileSprite->SetPosition(Position);
		Lifetime-2;
	}
}

/**
 * Sees if the projectile is within ranged of hiting the target
 *
 * \Damages the target if it hit
 */
void Projectile::DidItHit()
{
	Vector3 damagePos = Position + Direction * 1;

	if (userType == USERTYPE2::AI)
	{
		CEntity* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
	else if (userType == USERTYPE2::PLAYER)
	{
		CEntity* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}

}

/**
 * Sets up the projectile based on what weapon is using it, this makes sure that the right spriate is being used
 *
 * This also allows for the projectile to be at the right rotation when fireing
 */
void Projectile::StartUp(Vector3 dir, Vector3 pos, float speed, float lifetime, std::string projectile_name)
{
	Direction = dir;
	ProjectileSprite->SetPosition(pos);
	Position = pos;
	Lifetime = lifetime;

	if (projectile_name == "Arrow")
	{
		Speed = speed;
		ProjectileSprite->LoadTextureWIC("Resources/weapons/Arrow.png");
	}
	else if (projectile_name == "Fire")
	{
		Speed = speed * 2;
		ProjectileSprite->LoadTextureWIC("Resources/weapons/Wand - Fireball Projectile.png");
	}


	Vector3 up = { 0.0f, 1.0f, 0.0f };

	if (dir == Vector3(0, 0, 0))
		return;

	float dot = up.Dot(dir);
	float det = up.x * dir.y - up.y * dir.x;

	ProjectileSprite->SetRotation(atan2f(det, dot));
}


/**
 * Looks for the closest enemy within the range of the projectile
 *
 * \returns the enemy if within range
 */
CEntity* Projectile::GetClosestEnemy(Vector3 actorPos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > 50)
			break;

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

CEntity* Projectile::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > 50)
			break;

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