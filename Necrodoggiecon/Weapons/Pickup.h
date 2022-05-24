#pragma once
#include <Necrodoggiecon\Game\weapons.h>

class Pickup : public Weapon
{
public:
	Pickup();
	~Pickup();
	void Update(float deltaTime) override;
	virtual bool OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	CEntity* GetClosestEnemy(Vector3 actorPos, Vector3 damagePos);
	CEntity* GetClosestPlayer(Vector3 actorPos, Vector3 damagePos);

	void HandlePickup();
};

