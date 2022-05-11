#pragma once
#include <string>
#include <fstream>

#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Dependencies\NlohmannJson\json.hpp"

using json = nlohmann::json;

class weapons
{
public:
	weapons(std::string weapon);
	void LoadWeapons(std::string weapon);
	void OnFire();

private:
	void CoolDown(float attack_cooldown);

	std::string GetType();
	float GetDamage();
	float GetRange();
	float GetAttack_Speed();
	float GetAmmo();
	bool GetUnique();

	std::string type;
	float damage;
	float range;
	float attack_speed;
	float ammo;
	bool unique;
};

