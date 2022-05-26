/*****************************************************************//**
 * \file   HomingProjectile.h
 * \brief  Header containing all the functions and variables needed for Homing Projectile.
 *
 * \author Flynn Brooks
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <Necrodoggiecon/Projectile.h>
#include <Necrodoggiecon\Game\CCharacter.h>

class HomingProjectile : public Projectile
{
public:
	HomingProjectile();
	~HomingProjectile();

	virtual void Update(float deltaTime);
private:
	CAIController* GetClosestEnemy(Vector3 actorPos, float ranged);
	CCharacter* GetClosestPlayer(Vector3 actorPos, float ranged);
};

