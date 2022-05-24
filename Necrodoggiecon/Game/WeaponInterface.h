/*****************************************************************//**
 * \file   WeaponInterface.h
 * \brief  Interface class to implement the Weapons system using a Strategy Design Strategy
 * 
 * \author Ben Brown
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "weapons.h"
#include "Cerberus/Core/CComponent.h"

#include "Cerberus\Core\Engine.h"


class WeaponInterface : public CComponent
{
public:
	WeaponInterface();
	~WeaponInterface();

	virtual bool OnFire(Vector3 actorPos, Vector3 attackDir);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;

	void SetWeapon(Weapon* weapon);
	Weapon* GetCurrentWeapon() { return currentWeapon; };

	void SetUserType(USERTYPE userType);
	USERTYPE GetUserType() { return currentWeapon->GetUserType(); };
private:
	Weapon* currentWeapon = nullptr;

	USERTYPE userType = USERTYPE::AI;
};

