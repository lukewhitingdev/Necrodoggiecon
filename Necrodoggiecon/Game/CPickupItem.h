#pragma once
#include "Necrodoggiecon\Game\CEquippedItem.h"

class CPickupItem :  public CEquippedItem
{
public:
	virtual void Update(float deltaTime) override;
	virtual void Initialise(int id, CEntity* owner) override;
};

