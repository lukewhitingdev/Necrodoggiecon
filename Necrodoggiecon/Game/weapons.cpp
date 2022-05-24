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
	type = storedFile.at(weapon).at("Type");
	name = storedFile.at(weapon).at("Name");
	range = storedFile.at(weapon).at("Range");
	range = range * rangeScale;
	if (type != "Pickup")
	{
		projectileIconPath = storedFile.at(weapon).at("ProjectileIconPath");
		damage = storedFile.at(weapon).at("Damage");
		attack_speed = storedFile.at(weapon).at("Attack_Speed");
		ammo = storedFile.at(weapon).at("Ammo");
		unique = storedFile.at(weapon).at("Unique");
		cooldown = attack_speed;
	}
	else
	{
		pickupType = storedFile.at(weapon).at("PickupType");
	}

	Debug::Log("Range %f", range);
}

void Weapon::CoolDown(float attack_cooldown)
{
	if (canFire == false)
	{
		if (cooldown > 0)
		{
			cooldown -= 0.1f * attack_cooldown;
		}
		if (cooldown <= 0)
		{
			Debug::Log("Cooldown Done");
			canFire = true;
		}
	}
}

/**
 * OnFire function of base Weapon class, this is overridden in the MeleeWeapon and RangeWeapon sub-classes.
 * 
 * \param actorPos Position of the actor that is using the function (Used for virtual overriding)
 * \param attackDir Direction of the attack (Used for virtual overriding)
 */
void Weapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	Debug::Log("Base Weapon Class has fired Weapon: %s", name.c_str());
}

/**
 * Update function for Cooldown of weapons.
 * 
 * \param deltaTime
 */
void Weapon::Update(float deltaTime)
{
	CoolDown(deltaTime);
}

void Weapon::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}