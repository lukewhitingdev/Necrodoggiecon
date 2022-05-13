#include "weapons.h"
#include "Necrodoggiecon\Game\testCharacter.h"
#include <Necrodoggiecon\Game\AI\CAIController.h>

weapons::weapons(std::string weapon, USERTYPE userType)
{
	LoadWeapons(weapon);
	this->userType = userType;
}

void weapons::LoadWeapons(std::string weapon)
{
	std::ifstream file("Resources/Weapons.json");
	json storedFile;
	file >> storedFile;

	type = storedFile.at(weapon).at("Type");
	damage = storedFile.at(weapon).at("Damage");
	range = storedFile.at(weapon).at("Range");
	range = range * rangeScale;
	attack_speed = storedFile.at(weapon).at("Attack_Speed");
	ammo = storedFile.at(weapon).at("Ammo");
	unique = storedFile.at(weapon).at("Unique");
	cooldown = attack_speed;

	Debug::Log("Range %f", range);
}

void weapons::CoolDown(float deltaTime)
{
	if (cooldown > 0)
	{
		cooldown -= 0.1 * deltaTime;
	}
	if (cooldown <= 0)
	{
		Debug::Log("Cooldown Done");
		canFire = true;
	}
}

void weapons::Update(float deltaTime)
{
	if(!canFire)
	CoolDown(deltaTime);
}

void weapons::OnFire(Vector3 actorPos, Vector3 attackDir) //actorPos = Players position | attackDir = mouse position
{
	//Vector3 attackDir = attackDir - actorPos;
	auto normAttackDir = attackDir.Normalize();

	if (canFire)
	{
		Debug::Log("Can Fire");
		cooldown = attack_speed;
		if (type == "Melee")
		{
			Debug::Log("Melee\n");
			canFire = false;
			HandleMelee(actorPos, normAttackDir);
		}
		else if (type == "Melee")
		{
			Debug::Log("Melee\n");
		}
		else if (type == "Melee")
		{
			Debug::Log("Melee\n");
		}
		else
		{
			Debug::Log("Error\n");
		}
	}
}

void weapons::HandleMelee(Vector3 actorPos, Vector3 normAttackDir)
{
	Vector3 damagePos = actorPos + normAttackDir * range;

	if (userType == USERTYPE::AI)
	{
		CEntity* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
	else if (userType == USERTYPE::PLAYER)
	{
		CEntity* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
			Engine::DestroyEntity(target);
	}
	
}


//Gets closest enemy within attack range
CEntity* weapons::GetClosestEnemy(Vector3 actorPos)
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

CEntity* weapons::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<testCharacter*> players = Engine::GetEntityOfType<testCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	testCharacter* closestPlayer = nullptr;

	//Check each player
	for (testCharacter* player : players)
	{

		if (actorPos.DistanceTo(player->GetPosition()) > range)
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