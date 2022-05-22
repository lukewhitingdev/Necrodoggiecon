#include "weapons.h"
#include "Necrodoggiecon\Game\PlayerCharacter.h"
#include "Necrodoggiecon\Game\PlayerController.h"
#include <Cerberus\Core\AI\CAIController.h>

Weapon::Weapon(std::string weapon)
{
	SetWeapon(weapon);
}

/**
 * Sets the private variables using the information stored in a JSON file of weapons.
 * 
 * \param weapon Name of the weapon in the JSON
 */
void Weapon::SetWeapon(std::string weapon)
{
	std::ifstream file("Resources/Game/Weapons.json");
	json storedFile;
	file >> storedFile;

	iconPath = storedFile.at(weapon).at("IconPath");
	projectile_name = storedFile.at(weapon).at("Projectile_Name");
	type = storedFile.at(weapon).at("Type");
	name = storedFile.at(weapon).at("Name");
	damage = storedFile.at(weapon).at("Damage");
	range = storedFile.at(weapon).at("Range");
	range = range * rangeScale;
	attack_speed = storedFile.at(weapon).at("Attack_Speed");
	ammo = storedFile.at(weapon).at("Ammo");
	unique = storedFile.at(weapon).at("Unique");
	cooldown = attack_speed;

	Debug::Log("Range %f", range);
}

void Weapon::CoolDown(float attack_cooldown)
{
	if (!canFire)
	{
		if (cooldown > 0)
		{
			cooldown -= 0.1 * attack_cooldown;
		}
		if (cooldown <= 0)
		{
			Debug::Log("Cooldown Done");
			canFire = true;
		}
	}
}

/**
 * OnFire function that handles basic firing chekcing if the weapon is a Melee or Ranged weapon to use the basic logic. This will be overridden in the Sub-classes of weapons that have unique logic.
 * 
 * \param actorPos Position of the actor that is using the function
 * \param attackDir Direction of the attack
 */
void Weapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	Debug::Log("Weapon: %s", name.c_str());
	
	auto normAttackDir = attackDir.Normalize();

	if (canFire)
	{
		if (type == "Melee")
		{
			canFire = false;
			cooldown = attack_speed;
			HandleMelee(actorPos, normAttackDir);
		}
		else if (type == "Ranged")
		{
			if (ammo > 0)
			{
				canFire = false;
				cooldown = attack_speed;
				HandleRanged(actorPos, normAttackDir);
				ammo--;
			}
			else
			{
				canFire = false;
				Debug::Log("No ammo");
			}
		}
		else if (type == "Magic")
		{
			if (ammo > 0)
			{
				canFire = false;
				cooldown = attack_speed;
				HandleRanged(actorPos, normAttackDir);
				ammo--;
			}
			else
			{
				canFire = false;
				Debug::Log("No ammo");
			}
		}
	}
}

/**
 * Basic function to handle Melee.
 * 
 * \param actorPos Position of the actor that is using the function
 * \param normAttackDir Normalized direction of attack
 */
void Weapon::HandleMelee(Vector3 actorPos, Vector3 normAttackDir) // BB
{
	Vector3 damagePos = actorPos + normAttackDir * range;

	if (userType == USERTYPE::AI)
	{
		Debug::Log("UserType is AI");
		CEntity* target = GetClosestPlayer(actorPos, damagePos);
		if (target != nullptr)
		{
			playersController[0]->Unpossess();
			Engine::DestroyEntity(target);
		}
			
	}
	else if (userType == USERTYPE::PLAYER)
	{
		Debug::Log("UserType is PLAYER");
		CEntity* target = GetClosestEnemy(actorPos, damagePos);
		if (target != nullptr)
		{
			Engine::DestroyEntity(target);
		}
	}
}


void Weapon::HandleRanged(Vector3 actorPos, Vector3 attackDir)
{
	float speed = 4;
	Projectile* Projectile1 = Engine::CreateEntity<Projectile>();
	Projectile1->StartUp(attackDir, actorPos, speed, range, (int)userType, projectile_name);
}

/**
 * Gets closest enemy within attack range.
 *
 * \param actorPos Position of the object (Player or AI)
 * \param damagePos Position of the damage being dealt (actorPos + attackDirection * range)
 * 
 * \return closestEnemy CAIController Entity which is closest to the actorPos parameter position
 */
CEntity* Weapon::GetClosestEnemy(Vector3 actorPos, Vector3 damagePos)
{
	std::vector<CAIController*> enemies = Engine::GetEntityOfType<CAIController>();

	if (enemies.size() == 0) //No enemies
		return nullptr;

	CAIController* closestEnemy = nullptr;

	//Check each enemy
	for (CAIController* enemy : enemies)
	{

		if (actorPos.DistanceTo(enemy->GetPosition()) > range)
			continue;

		if (damagePos.DistanceTo(enemy->GetPosition()) > range)
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
CEntity* Weapon::GetClosestPlayer(Vector3 actorPos, Vector3 damagePos) // BB
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > range && damagePos.DistanceTo(player->GetPosition()) > range)
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

void Weapon::Update(float deltaTime)
{
	CoolDown(deltaTime);
}

void Weapon::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}