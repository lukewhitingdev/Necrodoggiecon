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
	float speed = Weapon::GetAttack_Speed() * 5;
	float life = Weapon::GetRange();
	Projectile* Projectile1 = Engine::CreateEntity<Projectile>();
	Projectile1->StartUp(attackDir, actorPos, speed, life);
}
