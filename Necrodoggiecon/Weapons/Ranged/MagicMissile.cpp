/*****************************************************************//**
 * \file   MagicMissile.cpp
 * \brief  All the functions needed for Magic Missile.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#include "MagicMissile.h"

MagicMissile::MagicMissile()
{
	Weapon::SetWeapon(4);
	RangeWeapon::SetProjectileSpeed(0.05f);
}

MagicMissile::~MagicMissile()
{
}

/**
 * Will spawn a homing projectile insaid of a normal projectile
 *
 * \Uses the onfire to make a homing projectile insaid of the other projectile
 */
bool MagicMissile::OnFire(Vector3 actorPos, Vector3 attackDir)
{
	if (Weapon::GetCanFire())
	{
		if (Weapon::GetAmmo() > 0)
		{
			auto normAttackDir = attackDir.Normalize();
			Weapon::SetCanFire(false);
			Weapon::StartCooldown();
			HomingProjectile* Projectile1 = Engine::CreateEntity<HomingProjectile>();
			Projectile1->StartUp(attackDir, actorPos, Weapon::GetDamage(), RangeWeapon::GetProjectileSpeed(), Weapon::GetRange(), (int)Weapon::GetUserType(), Weapon::GetProjectileIcon(), Weapon::GetHitSound());
			Weapon::SetAmmo(Weapon::GetAmmo() - 1);
			return true;
		}
		else
		{
			Weapon::SetCanFire(false);
		}
		return false;
	}
}
