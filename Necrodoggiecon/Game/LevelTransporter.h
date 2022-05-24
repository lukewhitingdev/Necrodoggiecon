#pragma once
#include "Necrodoggiecon/Game/CInteractable.h"
#include "Necrodoggiecon/CWorld_Game.h"
class LevelTransporter : public CInteractable
{
	LevelTransporter();
	void SetSlot(int SlotID) { Slot = SlotID; }

	virtual void OnInteract();

private: 

	int Slot;
};

