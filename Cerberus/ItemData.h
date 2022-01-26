#pragma once
#include <ItemDatabase.h>
#include <string>
#include <CEquippedItem.h>
#include <IInputable.h>

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

