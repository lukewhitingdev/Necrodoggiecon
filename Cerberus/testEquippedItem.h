#pragma once
#include "CEquippedItem.h"

class testEquippedItem : public CEquippedItem
{
public:
	virtual void Update(float deltaTime) override;
	virtual void Initialise(int id, CEntity* owner) override;
};

