#pragma once
#include <map>
#include <EquippedItem.h>

struct ItemData;

class ItemDatabase
{
private:
	static ItemDatabase* instance;
	ItemDatabase() {};
protected:
	std::map<int, ItemData*> itemDatabase;
	int GetNewID() { return (int)itemDatabase.size(); }

public:
	ItemData* GetItemFromID(int id);
	EquippedItem* CreateItemFromID(int id);

	void AddToMap(ItemData* dataToAdd);

	static ItemDatabase* Instance();
};

