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
	Debug::Log("FireBall");
	Weapon::SetWeapon(5);
	RangeWeapon::SetProjectileSpeed(4.0f);
}

Fireball::~Fireball()
{
}
