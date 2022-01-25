#include "CEquippedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CDroppedItem.h"

CEquippedItem::CEquippedItem()
{
}

CEquippedItem::~CEquippedItem()
{
}

void CEquippedItem::Update(float deltaTime)
{
}

void CEquippedItem::Initialise(int id, CEntity* newOwner)
{
	itemID = id;
	owner = newOwner;

	itemData = ItemDatabase::Instance()->GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();

}

void CEquippedItem::Equip()
{
}

void CEquippedItem::Unequip()
{
}

CDroppedItem* CEquippedItem::Drop()
{
	auto item = ItemDatabase::Instance()->CreateDroppedItemFromID(itemID);
	item->SetPosition(GetPosition());
	return item;
}
