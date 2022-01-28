#include "testEquippedItem.h"
#include "ItemData.h"

void testEquippedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//Get Owner Position
	auto pos = GetOwner()->GetPosition();
	//Add Offset
	pos.x += 25;
	pos.y += 25;

	//Set New Position
	SetPosition(pos);

	SetRotation(GetOwner()->GetRotation());
}

void testEquippedItem::Initialise(int id, CEntity* owner)
{
	CEquippedItem::Initialise(id, owner);
}
