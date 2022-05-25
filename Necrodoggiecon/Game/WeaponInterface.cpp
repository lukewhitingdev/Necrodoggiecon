#include "WeaponInterface.h"
#include <weaponUI.h>

WeaponInterface::WeaponInterface()
{
	currentWeapon = new Weapon("Dagger");
}

WeaponInterface::~WeaponInterface()
{
}

void WeaponInterface::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	currentWeapon->OnFire(actorPos, attackDir);
}

void WeaponInterface::Update(float deltaTime)
{
	
	currentWeapon->Update(deltaTime);
}

void WeaponInterface::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
}

void WeaponInterface::SetWeapon(Weapon* weapon)
{
	delete this->currentWeapon;
	currentWeapon = weapon;
	currentWeapon->SetUserType(userType);

	std::vector<weaponUI*> wepUIs = Engine::GetEntityOfType<weaponUI>();

	if(wepUIs.size() > 0)
	{
		weaponUI* wepUI = Engine::GetEntityOfType<weaponUI>()[0];
		wepUI->updateUI(currentWeapon->GetName(), -1, currentWeapon->GetAmmo(), currentWeapon->GetIconPath());
	}
}

void WeaponInterface::SetUserType(USERTYPE userType)
{
	this->userType = userType;
}
