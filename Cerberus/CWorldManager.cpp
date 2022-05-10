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
		if (EditorWorld != nullptr)
		{
			EditorWorld->UnloadWorld();
			EditorWorld->LoadWorld(Slot);
			EditorWorld->SetupWorld();
		}
		else
		{
			EditorWorld = new CWorld_Editable();
			EditorWorld->LoadWorld(Slot);
			EditorWorld->SetupWorld();

		}

		
		
		
	}
	else
	{
		if (EditorWorld != nullptr)
		{
			EditorWorld->UnloadWorld();
		}
		if (GameWorld == nullptr)
		{
			GameWorld = new CWorld();
			GameWorld->LoadWorld(Slot);
			GameWorld->SetupWorld();
		}
		else
		{
			GameWorld->UnloadWorld();
		}

	}



}

void CWorldManager::LoadWorld(CWorld* World)
{
	if (EditorWorld != nullptr)
	{
		EditorWorld->UnloadWorld();
	}
	else if (GameWorld != nullptr)
	{

	}
	else
	{
		GameWorld = World;
		GameWorld->SetupWorld();
	}
}

void CWorldManager::LoadWorld(CWorld_Editable* World)
{

	if (World != nullptr)
	{
		World->UnloadWorld();
	}
	else if (EditorWorld != nullptr)
	{

	}
	else
	{
		EditorWorld = World;
		EditorWorld->SetupWorld();
	}
}

