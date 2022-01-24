#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>

class DroppedItem : public CEntity
{
protected:
	CSpriteComponent* spriteComponent = nullptr;
	int itemID;
};

