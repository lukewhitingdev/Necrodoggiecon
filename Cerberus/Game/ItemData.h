#pragma once
#include <Cerberus\Game\ItemDatabase.h>
#include <string>
#include <Cerberus\Game\CEquippedItem.h>
#include <Cerberus\Core\Environment\IInputable.h>

struct ItemData
{
	std::string itemName;
	std::string texturePath;

	ItemData() {};
	ItemData(std::string name, std::string textureFilePath) : itemName(name), texturePath(textureFilePath)
	{
		ItemDatabase::AddToMap(this);
	}

	virtual CEquippedItem* CreateItem()
	{
		return Engine::CreateEntity<CEquippedItem>();
	}
};

