#include "TransitionHelper.h"
#include "Cerberus/Core/Utility/EntityManager.h"
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Necrodoggiecon/CWorld_Game.h"
#include "Necrodoggiecon/CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"

void TransitionHelper::OpenLevel(int Slot, bool isMenu)
{
	CUIManager::ClearAllCanvases();
	EntityManager::Purge();
	

	if (isMenu)
	{
		CWorldManager::LoadWorld(new CWorld_Menu());
	}
	else
	{
		CWorldManager::LoadWorld(new CWorld_Game(Slot));
	}
	

}
