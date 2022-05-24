/*****************************************************************//**
 * \file   Crossbow.cpp
 * \brief  All the functions needed for Crossbow.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "Crossbow.h"

Crossbow::Crossbow()
{
	Debug::Log("Crossbow");
	Weapon::SetWeapon("Crossbow");
	RangeWeapon::SetProjectileSpeed(4.0f);

	Weapon::SetScale(XMFLOAT3(0.5, 1.0, 1.0));
	Weapon::SetTextureOffset(XMFLOAT2(64.0, 0.0));
}

Crossbow::~Crossbow()
{
}

void Crossbow::Update(float deltaTime)
{
	Weapon::Update(deltaTime);

	if (Weapon::GetCanFire())
	{
		Weapon::SetTextureOffset(XMFLOAT2(64.0, 0.0));
	}
	else
	{
		Weapon::SetTextureOffset(XMFLOAT2(0.0, 0.0));
	}
}

