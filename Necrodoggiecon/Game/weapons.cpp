#include "weapons.h"
#include "Necrodoggiecon\Game\AI\CAIController.h"

Weapon::Weapon(std::string weapon)
{
	SetWeapon(NameToID(weapon));
}

/**
 * Sets the private variables using the information stored in a JSON file of weapons.
 * 
 * \param weapon Name of the weapon in the JSON
 */
void Weapon::SetWeapon(int ID)
{
	if (ID == -1)
	{
		Debug::Log("Invalid weapon ID");
		return;
	}
	std::ifstream file("Resources/Game/Weapons.json");
	if (file.is_open())
	{
		json storedFile;
		file >> storedFile;
		//iconPath = storedFile.at(weapon).at("IconPath");
		

		type = storedFile["Weapons"][ID]["Type"];
		name = storedFile["Weapons"][ID]["Name"];
		range = storedFile["Weapons"][ID]["Range"];
		iconPath = storedFile["Weapons"][ID]["IconPath"];

		range = range * rangeScale;
		if (type != "Pickup")
		{

			projectileIconPath = storedFile["Weapons"][ID]["ProjectileIconPath"];
			damage = storedFile["Weapons"][ID]["Damage"];
			attack_speed = storedFile["Weapons"][ID]["Attack_Speed"];
			maxAmmo = storedFile["Weapons"][ID]["Ammo"];
			ammo = maxAmmo;
			unique = storedFile["Weapons"][ID]["Unique"];
			cooldown = attack_speed;
		}
		else
		{
			pickupType = storedFile["Weapons"][ID]["PickupType"];
		}

		Debug::Log("Range %f", range);
	}
}

void Weapon::SetWeapon(std::string ID)
{
	SetWeapon(NameToID(ID));
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

std::string Weapon::IDToName(int ID)
{
	std::ifstream file("Resources/Weapons.json");
	json storedFile;
	file >> storedFile;
	

	std::string returnValue = storedFile["Weapons"][ID]["Name"];
	file.close();
	return returnValue;
}

int Weapon::NameToID(std::string Name)
{
	std::ifstream file("Resources/Weapons.json");
	json storedFile;
	file >> storedFile;
	std::string List[9];

	int Index = -1;
	for (int i = 0; i < storedFile["TotalWeapons"]; i++)
	{
		if (storedFile["Weapons"][i]["Name"] == Name)
			Index = i;
			break;
	}
	file.close();
	return Index;
}

/**
 * OnFire function of base Weapon class, this is overridden in the MeleeWeapon and RangeWeapon sub-classes.
 * 
 * \param actorPos Position of the actor that is using the function (Used for virtual overriding)
 * \param attackDir Direction of the attack (Used for virtual overriding)
 */
bool Weapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	return true;
}

/**
 * Update function for Cooldown of weapons.
 * 
 * \param deltaTime
 */
void Weapon::Update(float deltaTime)
{
	if (ammo > 0.0f || type == "Melee")
		CoolDown(deltaTime);
}

void Weapon::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}