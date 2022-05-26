/*****************************************************************//**
 * \file   Fireball.cpp
 * \brief  All the functions needed for fireball.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "Fireball.h"

Fireball::Fireball()
{
	Weapon::SetWeapon(5);
	RangeWeapon::SetProjectileSpeed(8.0f);
}

Fireball::~Fireball()
{
}
