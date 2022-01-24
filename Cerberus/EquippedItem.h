#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>

class EquippedItem : public CEntity
{
protected:
	CSpriteComponent* spriteComponent = nullptr;
	int itemID = 0;

	CEntity* owner = nullptr;

public:
	EquippedItem();
	virtual ~EquippedItem();

	// Inherited via CEntity
	virtual void Update(float deltaTime) override;

	void Initialise(int id);
};

