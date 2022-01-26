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
	UNREFERENCED_PARAMETER(deltaTime);
}

void CEquippedItem::Initialise(int id, CEntity* newOwner)
{
	itemID = id;
	owner = newOwner;

	itemData = ItemDatabase::GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	GetSpriteComponent()->LoadTexture(GetItemData()->texturePath);
	GetSpriteComponent()->SetRenderRect(XMUINT2(128, 128));
	GetSpriteComponent()->SetSpriteSize(XMUINT2(128, 128));

	Equip();
}

void CEquippedItem::Equip()
{
}

void CEquippedItem::Unequip()
{
}

CDroppedItem* CEquippedItem::Drop()
{
	Unequip();

	auto item = ItemDatabase::CreateDroppedItemFromID(itemID);
	item->SetPosition(GetPosition());
	return item;
}
