#pragma once

#include <Necrodoggiecon/Game/ItemData.h>
#include <Necrodoggiecon/Game/CEquippedItem.h>
#include <Cerberus/Core/Engine.h>
#include <Necrodoggiecon/Game/testEquippedItem.h>

struct EquippableItemData : public ItemData
{
	EquippableItemData(std::string name, std::string textureFilePath) : ItemData(name, textureFilePath)
	{
		itemType = ItemType::EQUIPPABLE;
	}
	virtual ~EquippableItemData() {};

	virtual CEquippedItem* CreateItem()
	{
		return Engine::CreateEntity<CEquippedItem>();
	}
};