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
	if (GetCanFire())
	{
		std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();
		
		if (enemies.size() == 0) //No enemies
			return;
		
		std::vector<CAIController*> enemiesCanHit;
		//Check each enemy
		for (CAIController* enemy : enemies)
		{
		
			if (actorPos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange() && attackDir.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
				continue;

			if (attackDir.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
				continue;

			Debug::Log("Longsword enemy stuff");

			
			enemiesCanHit.push_back(enemy);
		}
		for (int i = 0; i < enemiesCanHit.size(); i++)
			Engine::DestroyEntity(enemiesCanHit[i]);
	}
}

//std::vector<CEntity*> Longsword::GetPlayersInReach(Vector3 actorPos, Vector3 damagePos)
//{
//	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();
//
//	std::vector<CAIController*> enemiesCanHit;
//	if (enemies.size() == 0) //No enemies
//		return std::vector<CEntity*>();
//
//	CAIController* closestEnemy = nullptr;
//
//	//Check each enemy
//	for (CAIController* enemy : enemies)
//	{
//
//		if (actorPos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange() && damagePos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
//			continue;
//		
//		enemiesCanHit.push_back(enemy);
//	}
//
//	return enemiesCanHit;
//}
