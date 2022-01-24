#include "ItemDatabase.h"
#include "ItemData.h"

ItemDatabase* ItemDatabase::instance = nullptr;

ItemDatabase* ItemDatabase::Instance()
{
	if (instance == nullptr)
	{
		instance = new ItemDatabase();
	}
	return instance;
}

ItemData* ItemDatabase::GetItemFromID(int id)
{
	if (itemDatabase.count(id) > 0)
	{
		return itemDatabase[id];
	}

    return nullptr;
}

EquippedItem* ItemDatabase::CreateItemFromID(int id)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	EquippedItem* item = data->CreateItem();
	item->Initialise(id);
	return item;
}

void ItemDatabase::AddToMap(ItemData* dataToAdd)
{
	itemDatabase.insert(std::pair<int, ItemData*>(GetNewID(), dataToAdd));
	Debug::Log("%f", itemDatabase.size());
}

