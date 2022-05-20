#include "CDroppedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CEquippedItem.h"
/*****************************************************************//**
 * \file   CDroppedItem.cpp
 * \brief  Base class for items that have been dropped, most functionality is already handled in this class so inherited classes probably won't be needed
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
CDroppedItem::CDroppedItem()
{
}

CDroppedItem::~CDroppedItem()
{
}
/**
* Function used when a player interacts with a dropped item
* Will equip the dropped item to the player by creating a new EquippedItem with the DroppedItems data
* Will then destroy the DroppedItem
*/
CEquippedItem* CDroppedItem::OnEquip(CEntity* owner)
{
	auto item = ItemDatabase::CreateEquippedItemFromID(itemID, owner);
	Engine::DestroyEntity(this);
	return item;
}
/**
* Function used to initialise the DroppedItem with the correct ItemData
* Will get the ItemData from the ItemDatabase using the passed in id
* Will then set sprite data to the data from the retrieved ItemData
*/
void CDroppedItem::Initialise(int id)
{
	itemID = id;

	itemData = ItemDatabase::GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture(itemData->texturePath);
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));
}
/**
* Inherited function used to update the DroppedItem if necessary
*/
void CDroppedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
