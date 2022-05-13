#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Core/Environment/CWorld_Edit.h"

CWorld* CWorldManager::gameWorld = nullptr;
CWorld_Editable* CWorldManager::editorWorld = nullptr;

void CWorldManager::LoadWorld(int Slot, bool bEditorMode)
{
	if (bEditorMode)
	{
		if (gameWorld != nullptr)
		{
			gameWorld->UnloadWorld();
		}
		if (editorWorld != nullptr)
		{
			editorWorld->UnloadWorld();
			editorWorld->LoadWorld(Slot);
			editorWorld->SetupWorld();
		}
		else
		{
			editorWorld = new CWorld_Editable();
			editorWorld->LoadWorld(Slot);
			editorWorld->SetupWorld();

		}

		
		
		
	}
	else
	{
		if (editorWorld != nullptr)
		{
			editorWorld->UnloadWorld();
		}
		if (gameWorld == nullptr)
		{
			gameWorld = new CWorld();
			gameWorld->LoadWorld(Slot);
			gameWorld->SetupWorld();
		}
		else
		{
			gameWorld->UnloadWorld();
		}

	}



}

void CWorldManager::LoadWorld(CWorld* World)
{
	if (editorWorld != nullptr)
	{
		editorWorld->UnloadWorld();
	}
	else if (gameWorld != nullptr)
	{

	}
	else
	{
		gameWorld = World;
		gameWorld->SetupWorld();
	}
}

void CWorldManager::LoadWorld(CWorld_Editable* World)
{

	if (World != nullptr)
	{
		World->UnloadWorld();
	}
	else if (editorWorld != nullptr)
	{

	}
	else
	{
		editorWorld = World;
		editorWorld->SetupWorld();
	}
}

