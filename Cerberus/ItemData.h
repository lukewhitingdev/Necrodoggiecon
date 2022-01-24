#pragma once
#include <ItemDatabase.h>
#include <string>
#include <EquippedItem.h>

class ItemDatabase;

struct ItemData
{
	std::string itemName;
	std::string texturePath;

	ItemData() {};
	ItemData(std::string name, std::string textureFilePath) : itemName(name), texturePath(textureFilePath)
	{
		ItemDatabase::Instance()->AddToMap(this);
	}

	virtual EquippedItem* CreateItem()
	{
		return Engine::CreateEntity<EquippedItem>();
	}
};

