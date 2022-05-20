#include "ItemDatabase.h"
#include "ItemData.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
/*****************************************************************//**
 * \file   ItemDatabase.cpp
 * \brief  Class that stores a map of all ItemData, used to get ItemData from the items ID as well as, creating equipped and dropped items.
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
std::map<int, ItemData*> ItemDatabase::itemDatabase = {};

/**
 * .Will return the ItemData with the associated ID if it exists, if it doesn't it returns nullptr
 * 
 * \param id - The id to find ItemData for
 * \return - ItemData if the id exists in the database, otherwise will return null
 */
ItemData* ItemDatabase::GetItemFromID(int id)
{
	if (itemDatabase.count(id) > 0)
	{
		return itemDatabase[id];
	}

    return nullptr;
}
/**
 * Will create a new DroppedItem and initialise it with the passed in ID, if an ItemData with the ID doesn't exist it will return nullptr
 * 
 * \param id - The id to create a DroppedItem for
 * \return - The created DroppedItem or nullptr if the passed in id doesnt exist in the database
 */
CDroppedItem* ItemDatabase::CreateDroppedItemFromID(int id)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CDroppedItem* item = Engine::CreateEntity<CDroppedItem>();
	item->Initialise(id);
	return item;
}
/**
 * Will create a new EquippedItem and initialise it with the passed in ID, if an ItemData with the ID doesn't exist it will return nullptr.
 * 
 * \param id - The id to create an EquippedItem for
 * \param owner - The owner of the created EquippedItem
 * \return - The created EquippedItem or nullptr if the passed in ID does not exist in the database
 */
CEquippedItem* ItemDatabase::CreateEquippedItemFromID(int id, CEntity* owner)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CEquippedItem* item = data->CreateItem();
	item->Initialise(id, owner);
	return item;
}
/**
 * Will add the passed in ItemData to the itemDatabase and give it a unique ID.
 * 
 * \param dataToAdd - The ItemData to add to the database
 */
void ItemDatabase::AddToMap(ItemData* dataToAdd)
{
	itemDatabase.insert(std::pair<int, ItemData*>(GetNewID(), dataToAdd));
}

