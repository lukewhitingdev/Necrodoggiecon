/*****************************************************************//**
 * \file   RangedWeapon.cpp
 * \brief  All the functions needed for the Ranged Weapon.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "RangeWeapon.h"

RangeWeapon::RangeWeapon()
{
}

RangeWeapon::~RangeWeapon()
{
}

/**
 * Sees if there is any ammo in the weapon if there is then it will fire it
 *
 * \Gets the weapon system ready to make the projectile
 */
bool RangeWeapon::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	if (Weapon::GetCanFire())
	{
		if (Weapon::GetAmmo() > 0)
		{
			auto normAttackDir = attackDir.Normalize();
			Weapon::SetCanFire(false);
			Weapon::StartCooldown();
			HandleRanged(actorPos, normAttackDir);
			Weapon::SetAmmo(Weapon::GetAmmo() - 1);
			return true;
		}
		else
		{
			Weapon::SetCanFire(false);
		}
	}
	return false;
}

/**
 * Sets up the projectile
 *
 * \Spawns a projectile
 */
void RangeWeapon::HandleRanged(Vector3 actorPos, Vector3 attackDir)
{
	Projectile* Projectile1 = Engine::CreateEntity<Projectile>();
	Projectile1->StartUp(attackDir, actorPos, Weapon::GetDamage(), projectileSpeed, Weapon::GetRange(), (int)Weapon::GetUserType(), Weapon::GetProjectileIcon(), Weapon::GetHitSound());
}
