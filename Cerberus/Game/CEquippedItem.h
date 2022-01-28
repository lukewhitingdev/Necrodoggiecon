#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>

class CDroppedItem;
struct ItemData;

class CEquippedItem : public CEntity
{
private:
	CSpriteComponent* spriteComponent = nullptr;
	int itemID = 0;

	CEntity* itemOwner = nullptr;
	ItemData* itemData = nullptr;

protected:
	CSpriteComponent* GetSpriteComponent(){ return spriteComponent; }
	int GetItemID(){ return itemID; }

	CEntity* GetOwner() { return itemOwner; }
	ItemData* GetItemData() { return itemData; }
public:
	CEquippedItem();
	virtual ~CEquippedItem();

	virtual void Update(float deltaTime) override;

	virtual void Initialise(int id, CEntity* newOwner);

	virtual void Equip();
	virtual void Unequip();
	virtual CDroppedItem* Drop();
};

