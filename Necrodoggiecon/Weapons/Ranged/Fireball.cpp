#include "Fireball.h"

Fireball::Fireball()
{
	Debug::Log("FireBall");
	Weapon::SetWeapon("FireBall");
	RangeWeapon::SetProjectileSpeed(8.0f);
}

Fireball::~Fireball()
{
}
