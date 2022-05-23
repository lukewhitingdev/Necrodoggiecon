#include "HomingProjectile.h"
#include <Cerberus\Core\AI\CAIController.h>

HomingProjectile::HomingProjectile()
{
}

HomingProjectile::~HomingProjectile()
{
}

void HomingProjectile::Update(float deltaTime)
{
	if (Projectile::GetLifetime() > 0)
	{
		DidItHit();
		CAIController* target = GetClosestEnemy(Projectile::GetPosition(), 50000);
		if (target != nullptr)
		{
			Vector3 attack = target->GetPosition() - Projectile::GetPosition();
			Projectile::SetPosition(Projectile::GetPosition() + attack * (Projectile::GetSpeed() * deltaTime));
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