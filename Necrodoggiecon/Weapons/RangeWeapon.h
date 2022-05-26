/*****************************************************************//**
 * \file   RangedWeapon.h
 * \brief  Header containing all the functions and variables needed for the Ranged Weapon.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <Necrodoggiecon/Game/weapons.h>
class RangeWeapon : public Weapon
{
public:
	RangeWeapon();
	~RangeWeapon();

	virtual bool OnFire(Vector3 actorPos, Vector3 attackDir);

	void SetProjectileSpeed(float speed) { projectileSpeed = speed; };
	float GetProjectileSpeed() { return projectileSpeed; };
private:
	void HandleRanged(Vector3 actorPos, Vector3 attackDir);
	float projectileSpeed = 4;
};

