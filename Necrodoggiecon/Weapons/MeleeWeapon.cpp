#include "MeleeWeapon.h"
#include "Necrodoggiecon\Game\PlayerCharacter.h"
#include <Cerberus/Core/AI/CAIController.h>

MeleeWeapon::MeleeWeapon()
{
}

MeleeWeapon::~MeleeWeapon()
{
}

bool MeleeWeapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	if (Weapon::GetCanFire())
	{
		auto normAttackDir = attackDir.Normalize();
		Weapon::SetCanFire(false);
		Weapon::StartCooldown();
		HandleMelee(actorPos, normAttackDir);
		return true;
	}
	return false;
}

/**
 * Basic function to handle Melee.
 *
 * \param actorPos Position of the actor that is using the function
 * \param normAttackDir Normalized direction of attack
 */
void MeleeWeapon::HandleMelee(Vector3 actorPos, Vector3 normAttackDir) // BB
{
	Vector3 damagePos = actorPos + normAttackDir * Weapon::GetRange();

	if (Weapon::GetUserType() == USERTYPE::AI)
	{
		Debug::Log("UserType is AI");
		CEntity* target = GetClosestPlayer(actorPos, damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
	else if (Weapon::GetUserType() == USERTYPE::PLAYER)
	{
		Debug::Log("UserType is PLAYER");
		CEntity* target = GetClosestEnemy(actorPos, damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
}

/**
 * Gets closest enemy within attack range.
 *
 * \param actorPos Position of the object (Player or AI)
 * \param damagePos Position of the damage being dealt (actorPos + attackDirection * range)
 *
 * \return closestEnemy CAIController Entity which is closest to the actorPos parameter position
 */
CEntity* MeleeWeapon::GetClosestEnemy(Vector3 actorPos, Vector3 damagePos)
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
CEntity* MeleeWeapon::GetClosestPlayer(Vector3 actorPos, Vector3 damagePos) // BB
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