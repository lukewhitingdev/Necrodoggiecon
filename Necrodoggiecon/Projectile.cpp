/*****************************************************************//**
 * \file   Projectile.cpp
 * \brief  All the functions needed for the Projectile.
 * 
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "Projectile.h"
#include "Necrodoggiecon\Game\AI\CAIController.h"
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Cerberus/Core/Components/CAudioEmitterComponent.h>

Projectile::Projectile()
{
	ProjectileSprite = AddComponent<CSpriteComponent>(NAME_OF(ProjectileSprite));
	SetShouldMove(true);

	colComponent = new CollisionComponent("Projectile", this);
	colComponent->SetCollider(64.0f);
}

Projectile::~Projectile()
{
	//RemoveComponent(colComponent);
}

/**
 * Update for constantly moving projectile (Virtually overridden when unique logic is needed).
 *
 * \param deltaTime
 */
void Projectile::Update(float deltaTime)
{
	ProjectileSprite->SetPosition(GetPosition());
	if (initialPosition.DistanceTo(ProjectileSprite->GetPosition()) < Lifetime && hasHit == false)
	{
		DidItHit();
		Position += velocity * deltaTime;
		ProjectileSprite->SetPosition(Position);
		colComponent->SetPosition(GetPosition());
	}
	else if(hasHit == true)
	{
		Engine::DestroyEntity(this);
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
		{
			hasHit = true;
			target->ApplyDamage(Damage, onHitAudioPath);
			Lifetime = 0;
		}
	}
	else if (userType == USERTYPE2::PLAYER)
	{
		CAIController* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
		{
			hasHit = true;
			target->ApplyDamage(Damage, onHitAudioPath);
			Lifetime = 0;
		}
	}
}

/**
 * Sets up the projectile based on what weapon is using it, this makes sure that the right spriate is being used
 *
 * This also allows for the projectile to be at the right rotation when fireing
 */
void Projectile::StartUp(Vector3 dir, Vector3 pos, float damage, float speed, float lifetime, int type, const std::string &projectile_name, const std::string& hitAudioPath)
{
	Direction = dir;
	Damage = damage;
	Projectile_Name = projectile_name;
	Speed = speed * 100.0f;
	velocity = Direction * Speed;
	velocity.Truncate(Speed);
	Lifetime = lifetime;
	initialPosition = pos;
	Position = initialPosition;
	onHitAudioPath = hitAudioPath;
	ProjectileSprite->LoadTextureWIC(projectile_name);
	ProjectileSprite->SetRenderRect(XMUINT2(64, 64));
	ProjectileSprite->SetSpriteSize(XMUINT2(64, 64));

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