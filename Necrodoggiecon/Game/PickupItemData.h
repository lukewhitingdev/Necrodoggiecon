#pragma once

#include <Necrodoggiecon\Game\EquippableItemData.h>
#include <Necrodoggiecon\Game\CPickupItem.h>


struct PickupItemData : public EquippableItemData
{
	PickupType GetPickupType() { return pickupType; }
	float GetPickupStrength() { return pickupStrength; }
	float GetPickupTime() { return pickupTime; }

	PickupItemData(std::string name, std::string textureFilePath, PickupType type = PickupType::NECRODOGGICON_PAGE, float strength = 2.0f, float time = 5.0f) :
		EquippableItemData(name, textureFilePath), pickupType(type), pickupStrength(strength), pickupTime(time)
	{
		itemType = ItemType::PICKUP;
	}
	virtual ~PickupItemData() {  };

protected:
	PickupType pickupType;
	float pickupStrength = 2.0f;
	float pickupTime = 5.0f;
};