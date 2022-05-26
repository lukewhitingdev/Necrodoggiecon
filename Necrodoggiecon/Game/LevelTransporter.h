#pragma once
#include "Necrodoggiecon/Game/CInteractable.h"
#include "Necrodoggiecon/CWorld_Game.h"
class LevelTransporter : public CInteractable
{
public:
	LevelTransporter();
	void SetSlot(int SlotID) { Slot = SlotID; }

	virtual void OnInteract();
	int GetSlot() { return Slot; }
private: 

	int Slot;
};

