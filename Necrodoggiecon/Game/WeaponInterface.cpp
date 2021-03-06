#include "WeaponInterface.h"
#include <weaponUI.h>
#include "Necrodoggiecon/Game/PlayerCharacter.h"

WeaponInterface::WeaponInterface()
{
}

WeaponInterface::~WeaponInterface()
{
}

/**
 * OnFire Function calls CurrentWeapon OnFire, this OnFire is overidden through virtual functions in the Sub-Classes.
 * 
 * \param actorPos
 * \param attackDir
 */
bool WeaponInterface::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	bool ret = currentWeapon->OnFire(actorPos, attackDir);

	std::vector<weaponUI*> wepUIs = Engine::GetEntityOfType<weaponUI>();

	if (wepUIs.size() > 0)
	{
		weaponUI* wepUI = Engine::GetEntityOfType<weaponUI>()[0];
		wepUI->updateUI(currentWeapon->GetName(), currentWeapon->GetAmmo(), currentWeapon->GetMaxAmmo(), currentWeapon->GetIconPath());
	}
	return ret;
}

void WeaponInterface::Update(float deltaTime)
{
	currentWeapon->Update(deltaTime);
}

void WeaponInterface::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}

/**
 * Function to delete previous weapon from memory and set in use weapon.
 * 
 * \param weapon
 */
void WeaponInterface::SetWeapon(Weapon* weapon)
{
	currentWeapon = weapon;
	currentWeapon->SetUserType(userType);

	CEntity* parent = GetParent();
	CCharacter* character = dynamic_cast<CCharacter*>(parent);
	if(character != nullptr && character->GetIsPlayer())
	{
		std::vector<weaponUI*> wepUIs = Engine::GetEntityOfType<weaponUI>();

		if (wepUIs.size() > 0)
		{
			weaponUI* wepUI = Engine::GetEntityOfType<weaponUI>()[0];
			wepUI->updateUI(currentWeapon->GetName(), currentWeapon->GetAmmo(), currentWeapon->GetMaxAmmo(), currentWeapon->GetIconPath());
		}
	}
}

/**
 * Sets type of user using the weapon.
 * 
 * \param userType
 */
void WeaponInterface::SetUserType(USERTYPE userType)
{
	this->userType = userType;
}
