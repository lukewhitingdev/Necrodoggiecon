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

void weapons::CoolDown(float attack_cooldown)
{
	while (attack_cooldown > 0)
	{
		// cant attack
		attack_cooldown - 0.1;
	}
}

void weapons::OnFire()
{
	float num;

	num = GetAttack_Speed();
	CoolDown(num);
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