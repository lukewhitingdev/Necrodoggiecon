#pragma once
#include <Necrodoggiecon/Weapons/RangeWeapon.h>
#include <Necrodoggiecon/HomingProjectile.h>

class MagicMissile : public RangeWeapon
{
public:
	MagicMissile();
	~MagicMissile();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:

};

