#include "RangeWeapon.h"

RangeWeapon::RangeWeapon()
{
}

RangeWeapon::~RangeWeapon()
{
}

void RangeWeapon::OnFire(Vector3 actorPos, Vector3 attackDir)
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
		}
		else
		{
			Weapon::SetCanFire(false);
			Debug::Log("No Ammo!!!");
		}
	}
}

void RangeWeapon::HandleRanged(Vector3 actorPos, Vector3 attackDir)
{
	Projectile* Projectile1 = Engine::CreateEntity<Projectile>();
	Projectile1->StartUp(attackDir, actorPos, Weapon::GetDamage(), projectileSpeed, Weapon::GetRange(), (int)Weapon::GetUserType(), Weapon::GetProjectileIcon(), Weapon::GetHitSoundPath());
}
