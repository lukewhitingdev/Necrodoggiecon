#include "CEquippedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CDroppedItem.h"
/*****************************************************************//**
 * \file   CEquippedItem.cpp
 * \brief  Base class for items that can be equipped.
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
CEquippedItem::CEquippedItem()
{
}

CEquippedItem::~CEquippedItem()
{
}
/**
* Inherited function used to update the EquippedItem if necessary
*/
void CEquippedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/**
 * Function used to initialise the EquippedItem with the correct ItemData
 * Will get the ItemData from the ItemDatabase using the passed in id
 * Will then set sprite data to the data from the retrieved ItemData
 * Will then call the virtual Equip function for any necessary additional setup
 * 
 * \param id - The id of the item being stored
 * \param newOwner - The entity that owns the equipped item
 */
void CEquippedItem::Initialise(int id, CEntity* newOwner)
{
	itemID = id;
	itemOwner = newOwner;

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
/**
 * Function used to create a DroppedItem using the id stored on the EquippedItem
 * 
 * \return - Returns the created dropped item
 */
CDroppedItem* CEquippedItem::Drop()
{
	Unequip();

	auto item = ItemDatabase::CreateDroppedItemFromID(itemID);
	item->SetPosition(GetPosition());
	Engine::DestroyEntity(this);
	return item;
}
