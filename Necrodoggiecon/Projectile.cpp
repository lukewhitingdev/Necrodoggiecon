/*****************************************************************//**
 * \file   Projectile.cpp
 * \brief  All the functions needed for the Projectile.
 * 
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "Projectile.h"
#include <Cerberus\Core\AI\CAIController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>

Projectile::Projectile()
{
	ProjectileSprite = AddComponent<CSpriteComponent>();
	ProjectileSprite->SetRenderRect(XMUINT2(64, 64));
	ProjectileSprite->SetSpriteSize(XMUINT2(64, 64));
}

Projectile::~Projectile()
{
	//RemoveComponent(colComponent);
}

/**
 * .
 *
 * \param deltaTime
 */
void Projectile::Update(float deltaTime)
{
	if (Projectile_Name != "Missle")
	{
		if (initialPosition.DistanceTo(ProjectileSprite->GetPosition()) < Lifetime)
		{
			DidItHit();
			Position += Direction * Speed;
			ProjectileSprite->SetPosition(Position);
		}
		else
		{
			Engine::DestroyEntity(this);
		}
	}
	else if (Projectile_Name == "Missle")
	{
		if (Lifetime > 0)
		{
			DidItHit();
			CAIController* target = GetClosestEnemy(Position, 50000);
			if (target != nullptr)
			{
				Vector3 attack = target->GetPosition() - Position;
				Position += attack * (Speed * deltaTime);
				ProjectileSprite->SetPosition(Position);
				Lifetime - 2;
			}
			else
			{
				Position += Direction * Speed;
				ProjectileSprite->SetPosition(Position);
			}
		}
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
		PlayerCharacter* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
			target->ApplyDamage(Damage, GetClosestEnemy(damagePos));
	}
	else if (userType == USERTYPE2::PLAYER)
	{
		CAIController* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
		{
			target->ApplyDamage(Damage, GetClosestPlayer(damagePos));
			Lifetime = 0;
			ProjectileSprite->SetSpriteSize(XMUINT2(0, 0));

		}
	}
}

/**
 * Sets up the projectile based on what weapon is using it, this makes sure that the right spriate is being used
 *
 * This also allows for the projectile to be at the right rotation when fireing
 */
void Projectile::StartUp(Vector3 dir, Vector3 pos, float damage, float speed, float lifetime, int type, const std::string projectile_name)
{
	Direction = dir;
	ProjectileSprite->SetPosition(pos);
	Damage = damage;
	Projectile_Name = projectile_name;
	Speed = speed;
	Lifetime = lifetime;
	initialPosition = pos;

	if (projectile_name == "Arrow")
	{
		Speed = speed;
		ProjectileSprite->LoadTextureWIC("Resources/Game/weapons/Arrow.png");
	}
	else if (projectile_name == "Fire")
	{
		Speed = speed * 2;
		ProjectileSprite->LoadTextureWIC("Resources/Game/weapons/Wand - Fireball Projectile.png");
	}
	else if (projectile_name == "Missle")
	{
		Speed = speed;
		ProjectileSprite->LoadTextureWIC("Resources/Game/weapons/Wand - Magic missile Projectile.png");
	}

	userType = (USERTYPE2)type;

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

CAIController* Projectile::GetClosestEnemy(Vector3 actorPos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > 50)
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

CAIController* Projectile::GetClosestEnemy(Vector3 actorPos, float ranged)
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



PlayerCharacter* Projectile::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > 50)
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