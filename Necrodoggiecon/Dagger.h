#pragma once
#include <Necrodoggiecon\Game\weapons.h>

class Dagger : public Weapon
{
public:
	Dagger();
	~Dagger();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	
};

