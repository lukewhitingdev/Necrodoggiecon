#include "EquippedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"

EquippedItem::EquippedItem()
{
}

EquippedItem::~EquippedItem()
{
}

void EquippedItem::Update(float deltaTime)
{
}

void EquippedItem::Initialise(int id)
{
	itemID = id;
	auto data = ItemDatabase::Instance()->GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture(data->texturePath);
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));
	Debug::Log("created");
}
