#include "Pickup.h"
#include "Necrodoggiecon\Game\PlayerCharacter.h"
#include <Cerberus/Core/AI/CAIController.h>

Pickup::Pickup()
{
}

Pickup::~Pickup()
{
}

void Pickup::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	HandlePickup();
}

/**
 * Gets closest enemy within attack range.
 *
 * \param actorPos Position of the object (Player or AI)
 * \param damagePos Position of the damage being dealt (actorPos + attackDirection * range)
 *
 * \return closestEnemy CAIController Entity which is closest to the actorPos parameter position
 */
CEntity* Pickup::GetClosestEnemy(Vector3 actorPos, Vector3 damagePos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
			continue;

		if (damagePos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
			continue;

		Debug::Log("Enemy is in range");

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
 * Gets Closest Player within attack range.
 *
 * \param actorPos Position of the object (Player or AI)
 * \param damagePos Position of the damage being dealt (actorPos + attackDirection * range)
 *
 * \return closestPlayer PlayerCharacter entity that is closest to the actorPos parameter position
 */
CEntity* Pickup::GetClosestPlayer(Vector3 actorPos, Vector3 damagePos) // BB
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > Weapon::GetRange() && damagePos.DistanceTo(player->GetPosition()) > Weapon::GetRange())
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
void Pickup::HandlePickup()
{
	
	CEntity* player = GetClosestPlayer(GetPosition(), GetPosition());
	IUsePickup* usePickup = dynamic_cast<IUsePickup*>(player);
	if (usePickup == nullptr) return;

	usePickup->UsePickup(pickupType, 5.0f);
}
