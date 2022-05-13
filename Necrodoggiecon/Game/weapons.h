#pragma once
#include <string>
#include <fstream>

#include <Cerberus\Core\CEntity.h>
#include "Cerberus\Core\Engine.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

#define rangeScale 320.0f

using json = nlohmann::json;

enum class USERTYPE
{
	PLAYER,
	AI,
};

class weapons : public CEntity
{
public:
	weapons(std::string weapon, USERTYPE userType);
	void LoadWeapons(std::string weapon);
	virtual void OnFire(Vector3 actorPos, Vector3 attackPos);
	virtual void Update(float deltaTime) override;

private:
	void CoolDown(float attack_cooldown);

	std::string GetType() { return type; };
	float GetDamage() { return damage; };
	float GetRange() { return range; };
	float GetAttack_Speed() { return attack_speed; };
	float GetAmmo() { return ammo; };
	bool GetUnique() { return unique; };
	USERTYPE GetUserType() { return userType; };

	void HandleMelee(Vector3 actorPos, Vector3 normAttackDir);
	void HandleRanged();

	CEntity* GetClosestEnemy(Vector3 actorPos);
	CEntity* GetClosestPlayer(Vector3 actorPos);

	std::string type;
	float damage;
	float range;
	float attack_speed;
	float ammo;
	bool unique;

	USERTYPE userType;

protected:
	
};

