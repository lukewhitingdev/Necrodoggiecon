#pragma once
#include <Necrodoggiecon/Projectile.h>
class HomingProjectile : public Projectile
{
public:
	HomingProjectile();
	~HomingProjectile();

	virtual void Update(float deltaTime);
private:
	CAIController* GetClosestEnemy(Vector3 actorPos, float ranged);
};

