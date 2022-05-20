#include "weapons.h"
#include "Necrodoggiecon\Game\PlayerCharacter.h"
#include "Necrodoggiecon\Game\PlayerController.h"
#include <Cerberus\Core\AI\CAIController.h>
#include <Game\IUsePickup.h>
Weapon::Weapon()
{
	SetWeapon("Crossbow");
}

void Weapon::SetWeapon(std::string weapon)
{
	std::ifstream file("Resources/Weapons.json");
	json storedFile;
	file >> storedFile;

	type = storedFile.at(weapon).at("Type");
	if (type != "Pickup")
	{
		damage = storedFile.at(weapon).at("Damage");
		range = storedFile.at(weapon).at("Range");
		range = range * rangeScale;
		attack_speed = storedFile.at(weapon).at("Attack_Speed");
		ammo = storedFile.at(weapon).at("Ammo");
		unique = storedFile.at(weapon).at("Unique");
		cooldown = attack_speed;
	}
	else
	{
		pickupType == storedFile.at(weapon).at("PickupType");
	}

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

void Weapon::OnFire(Vector3 actorPos, Vector3 attackDir) //actorPos = Players position | attackDir = mouse position
{
	//Vector3 attackDir = attackDir - actorPos;
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
	}
}


void Weapon::HandleMelee(Vector3 actorPos, Vector3 normAttackDir)
{
	Vector3 damagePos = actorPos + normAttackDir * range;

	if (userType == USERTYPE::AI)
	{
		CEntity* target = GetClosestPlayer(damagePos);
		if (target != nullptr)
		{
			playersController[0]->Unpossess();
			Engine::DestroyEntity(target);
		}
			
	}
	else if (userType == USERTYPE::PLAYER)
	{
		CEntity* target = GetClosestEnemy(damagePos);
		if (target != nullptr)
		{
			Engine::DestroyEntity(target);
		}
	}
}


void Weapon::HandleRanged(Vector3 actorPos, Vector3 attackDir)
{
	float speed = attack_speed * 5;
	float life = range;
	Projectile* Projectile1 = Engine::CreateEntity<Projectile>();
	Projectile1->StartUp(attackDir, actorPos, speed, life, (int)userType);
}

void Weapon::HandlePickup()
{
	auto player = GetClosestPlayer(GetPosition());
	IUsePickup* usePickup = dynamic_cast<IUsePickup*>(player);
	usePickup->UsePickup(pickupType, 5.0f);
}

//Gets closest enemy within attack range
CEntity* Weapon::GetClosestEnemy(Vector3 actorPos)
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

CEntity* Weapon::GetClosestPlayer(Vector3 actorPos)
{
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	if (players.size() == 0) //No players
		return nullptr;

	PlayerCharacter* closestPlayer = nullptr;

	//Check each player
	for (PlayerCharacter* player : players)
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

void Weapon::Update(float deltaTime)
{
	CoolDown(deltaTime);
}

void Weapon::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}