#include "ItemDatabase.h"
#include "ItemData.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"

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

CDroppedItem* ItemDatabase::CreateDroppedItemFromID(int id)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CDroppedItem* item = Engine::CreateEntity<CDroppedItem>();
	item->Initialise(id);
	return item;
}

CEquippedItem* ItemDatabase::CreateEquippedItemFromID(int id, CEntity* owner)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CEquippedItem* item = data->CreateItem();
	item->Initialise(id, owner);
	return item;
}

void ItemDatabase::AddToMap(ItemData* dataToAdd)
{
	itemDatabase.insert(std::pair<int, ItemData*>(GetNewID(), dataToAdd));
}

