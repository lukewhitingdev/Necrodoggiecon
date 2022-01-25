#include "testEquippedItem.h"
#include "ItemData.h"

void testEquippedItem::Update(float deltaTime)
{
	auto pos = GetOwner()->GetPosition();
	pos.x += 25;
	pos.y += 25;

	SetPosition(pos);
}

void testEquippedItem::Initialise(int id, CEntity* owner)
{
	CEquippedItem::Initialise(id, owner);

	GetSpriteComponent()->LoadTexture(GetItemData()->texturePath);
	GetSpriteComponent()->SetRenderRect(XMUINT2(128, 128));
	GetSpriteComponent()->SetSpriteSize(XMUINT2(128, 128));
}
