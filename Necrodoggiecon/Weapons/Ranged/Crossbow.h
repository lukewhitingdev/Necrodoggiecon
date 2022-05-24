#pragma once
#include <Necrodoggiecon/Weapons/RangeWeapon.h>

class Crossbow : public RangeWeapon
{
public:
	Crossbow();
	~Crossbow(); 

	virtual void Update(float deltaTime);
};

