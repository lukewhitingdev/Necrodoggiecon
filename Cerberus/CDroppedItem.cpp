#include "CDroppedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CEquippedItem.h"

CDroppedItem::CDroppedItem()
{
}

CDroppedItem::~CDroppedItem()
{
}

CEquippedItem* CDroppedItem::OnEquip(CEntity* owner)
{
	return ItemDatabase::Instance()->CreateEquippedItemFromID(itemID, owner);
}

void CDroppedItem::Initialise(int id)
{
	itemID = id;

	itemData = ItemDatabase::Instance()->GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture(itemData->texturePath);
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));
}

void CDroppedItem::Update(float deltaTime)
{
}
