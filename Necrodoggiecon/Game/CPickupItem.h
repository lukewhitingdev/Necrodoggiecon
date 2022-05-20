#pragma once
#include "Necrodoggiecon\Game\CInteractable.h"
enum class PickupType
{
	NECRODOGGICON_PAGE,
	SHIELD_SCROLL,
	INVISIBILITY_SCROLL,
	CHARM_SCROLL,
	SEEING_SCROLL
};
class CPickupItem :  public CInteractable
{
public:
	virtual void Update(float deltaTime) override;
	virtual void OnInteract() override;
protected:
	PickupType pickupType = PickupType::INVISIBILITY_SCROLL;
};

