#pragma once
#include <map>

class CEquippedItem;
class CDroppedItem;
class CEntity;

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
	CEquippedItem* CreateEquippedItemFromID(int id, CEntity* owner);
	CDroppedItem* CreateDroppedItemFromID(int id);

	void AddToMap(ItemData* dataToAdd);

	static ItemDatabase* Instance();
};

