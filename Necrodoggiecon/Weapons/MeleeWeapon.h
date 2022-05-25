#pragma once
#include <Necrodoggiecon\Game\weapons.h>
#include <Necrodoggiecon\Game\CCharacter.h>

class MeleeWeapon : public Weapon
{
public:
	MeleeWeapon();
	~MeleeWeapon();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	CCharacter* GetClosestEnemy(Vector3 actorPos, Vector3 damagePos);
	CCharacter* GetClosestPlayer(Vector3 actorPos, Vector3 damagePos);

	void HandleMelee(Vector3 actorPos, Vector3 normAttackDir);
};

