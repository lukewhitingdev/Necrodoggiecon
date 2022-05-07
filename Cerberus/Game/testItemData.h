#pragma once
#include "ItemData.h"
#include <Cerberus\Game\ItemDatabase.h>
#include "testEquippedItem.h"

struct testItemData :  public ItemData
{
	testItemData(std::string name, std::string textureFilePath) : ItemData(name, textureFilePath)
	{
	}
	virtual CEquippedItem* CreateItem()
	{
		return Engine::CreateEntity<testEquippedItem>();
	}
};

