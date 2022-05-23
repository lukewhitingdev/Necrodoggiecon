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
