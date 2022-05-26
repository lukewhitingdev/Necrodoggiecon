#include "Longsword.h"
#include <Necrodoggiecon/Game/AI/CAIController.h>
#include <Necrodoggiecon/Game/PlayerCharacter.h>

Longsword::Longsword()
{
	Weapon::SetWeapon(2);
}

Longsword::~Longsword()
{
}

/**
 * Virtual override OnFire containing unique sweeping logic.
 * 
 * \param actorPos
 * \param attackDir
 */
bool Longsword::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	auto normAttackDir = attackDir.Normalize();

	Vector3 damagePos = actorPos + normAttackDir * Weapon::GetRange();

	if (GetCanFire())
	{
		if (Weapon::GetUserType() == USERTYPE::PLAYER)
		{
			std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();
			StartCooldown();
			SetCanFire(false);
			if (enemies.size() == 0) //No enemies
				return true;

			//Check each enemy
			for (CAIController* enemy : enemies)
			{

				if (actorPos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
					continue;

				if (damagePos.DistanceTo(enemy->GetPosition()) > Weapon::GetRange())
					continue;

				enemy->ApplyDamage(GetDamage());
			}
		}
		else if (Weapon::GetUserType() == USERTYPE::AI)
		{
			std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();
			StartCooldown();
			SetCanFire(false);
			if (players.size() == 0) //No enemies
				return true;

			//Check each enemy
			for (PlayerCharacter* player : players)
			{

				if (actorPos.DistanceTo(player->GetPosition()) > Weapon::GetRange())
					continue;

				if (damagePos.DistanceTo(player->GetPosition()) > Weapon::GetRange())
					continue;

				player->ApplyDamage(GetDamage());
			}
		}
		return true;
	}
	return false;
}
