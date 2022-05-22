#pragma once
#include <Necrodoggiecon/Game/weapons.h>
class RangeWeapon : public Weapon
{
public:
	RangeWeapon();
	~RangeWeapon();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	void HandleRanged(Vector3 actorPos, Vector3 attackDir);
};

