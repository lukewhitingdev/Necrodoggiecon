#include "weapons.h"

weapons::weapons(std::string weapon)
{
	LoadWeapons(weapon);
}

void weapons::LoadWeapons(std::string weapon)
{
	std::ifstream file("Resources/Weapons.json");
	json storedFile;
	file >> storedFile;

	type = storedFile.at(weapon).at("Type");
	damage = storedFile.at(weapon).at("Damage");
	range = storedFile.at(weapon).at("Range");
	attack_speed = storedFile.at(weapon).at("Attack_Speed");
	ammo = storedFile.at(weapon).at("Ammo");
	unique = storedFile.at(weapon).at("Unique");
}

void weapons::CoolDown(float attack_cooldown, std::string weapon)
{
	std::string weaponsave = weapon;
	do
	{
		weapon = "NULL";
		Debug::Log("Cooldown");
		attack_cooldown - 0.01;
	} while (attack_cooldown >= 0);
	weapon = weaponsave;
}

void weapons::OnFire(std::string weapon)
{
	float num;
	num = GetAttack_Speed();

	if (weapon == "Melee")
	{
		Debug::Log("Melee\n");
		CoolDown(num, weapon);
	}
	else if (weapon == "Ranged")
	{
		Debug::Log("Ranged\n");
		CoolDown(num, weapon);
	}
	else if (weapon == "Magic")
	{
		Debug::Log("Magic\n");
		CoolDown(num, weapon);
	}
	else
	{
		Debug::Log("Error\n");
	}
}



std::string weapons::GetType()
{
	return type;
}

float weapons::GetDamage()
{
	return damage;
}

float weapons::GetRange()
{
	return range;
}

float weapons::GetAttack_Speed()
{
	return attack_speed;
}

float weapons::GetAmmo()
{
	return ammo;
}

bool weapons::GetUnique()
{
	return unique;
}