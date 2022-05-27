#include "TransitionHelper.h"
#include "Cerberus/Core/Utility/EntityManager.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Necrodoggiecon/CWorld_Game.h"
#include "Necrodoggiecon/CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"

int TransitionHelper::queueSlot = 0;
bool TransitionHelper::queueMenu = false;

void TransitionHelper::OpenLevel(int Slot, bool isMenu)
{
	CUIManager::ClearAllCanvases();
	EntityManager::Purge();
	queueSlot = Slot;
	queueMenu = isMenu;
}

void TransitionHelper::OpenQueuedLevel()
{

	if (queueMenu)
	{
		CWorldManager::LoadWorld(new CWorld_Menu());
	}
	else
	{
		CWorldManager::LoadWorld(new CWorld_Game(queueSlot));
	}
}
