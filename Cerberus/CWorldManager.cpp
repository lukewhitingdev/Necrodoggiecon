#include "CWorldManager.h"
#include "Core/Environment/CWorld_Edit.h"

CWorld* CWorldManager::GameWorld = nullptr;
CWorld_Editable* CWorldManager::EditorWorld = nullptr;

void CWorldManager::LoadWorld(int Slot, bool bEditorMode)
{
	if (bEditorMode)
	{
		if (GameWorld != nullptr)
		{
			GameWorld->UnloadWorld();
		}

		EditorWorld = new CWorld_Editable();
		EditorWorld->LoadWorld_Edit(Slot);
		
	}
	else
	{
		if (EditorWorld != nullptr)
		{

		}
		if (GameWorld == nullptr)
		{
			GameWorld = new CWorld();
			GameWorld->LoadWorld(Slot);
		}
		else
		{
			GameWorld->UnloadWorld();
		}

	}



}
