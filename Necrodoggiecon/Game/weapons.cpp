#include "weapons.h"
#include "Necrodoggiecon\Game\AI\CAIController.h"

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

	hitSoundPath = storedFile.at(weapon).at("HitAudioPath");
	attackSoundPath = storedFile.at(weapon).at("AttackAudioPath");
	ammo = storedFile.at(weapon).at("Ammo");

	if (type != "Pickup")
	{
		projectileIconPath = storedFile.at(weapon).at("ProjectileIconPath");
		damage = storedFile.at(weapon).at("Damage");
		attack_speed = storedFile.at(weapon).at("Attack_Speed");
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
 * OnFire function that handles basic firing chekcing if the weapon is a Melee or Ranged weapon to use the basic logic. This will be overridden in the Sub-classes of weapons that have unique logic.
 * 
 * \param actorPos Position of the actor that is using the function (Used for virtual overriding)
 * \param attackDir Direction of the attack (Used for virtual overriding)
 */
bool Weapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	Debug::Log("Base Weapon Class has fired Weapon: %s", name.c_str());
	return true;
}

void Weapon::Update(float deltaTime)
{
	CoolDown(deltaTime);
}

void Weapon::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}