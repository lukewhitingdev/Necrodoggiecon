#pragma once
#include <Necrodoggiecon\Game\weapons.h>

class MeleeWeapon : public Weapon
{
public:
	MeleeWeapon();
	~MeleeWeapon();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	CEntity* GetClosestEnemy(Vector3 actorPos, Vector3 damagePos);
	CEntity* GetClosestPlayer(Vector3 actorPos, Vector3 damagePos);

	void HandleMelee(Vector3 actorPos, Vector3 normAttackDir);
};

