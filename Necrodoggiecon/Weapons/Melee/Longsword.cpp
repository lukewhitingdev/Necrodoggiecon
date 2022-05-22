#include "Longsword.h"
#include <Necrodoggiecon\Game\AI\CAIController.h>

Longsword::Longsword()
{
	Debug::Log("Longsword");
	Weapon::SetWeapon("Longsword");
}

Longsword::~Longsword()
{
}

void Longsword::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	auto normAttackDir = attackDir.Normalize();

	Vector3 damagePos = actorPos + normAttackDir * Weapon::GetRange();

	if (GetCanFire())
	{
		Debug::Log("Longsword damage pos %f %f", actorPos.x, actorPos.y);
		std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();
		StartCooldown();
		SetCanFire(false);
		if (enemies.size() == 0) //No enemies
			return;
		
		std::vector<CAIController*> enemiesCanHit;
		//Check each enemy
		for (CAIController* enemy : enemies)
		{
		
			if (actorPos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
				continue;

			if (damagePos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
				continue;

			Debug::Log("Longsword enemy stuff");

			Engine::DestroyEntity(enemy);
			
		}
	}
}
