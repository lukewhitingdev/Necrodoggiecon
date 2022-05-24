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
}

Crossbow::~Crossbow()
{
}
