/*******************************************************************
 * \file   CWorldManager.cpp
 * \brief  Handles level loading and unloading as well as makes accessing active level available anywhere in the project.
 * 
 * \author sam-j
 * \date   May 2022
 *********************************************************************/
#include "Cerberus/Core/Utility/CWorldManager.h"
#include "Core/Environment/CWorld_Edit.h"

CWorld* CWorldManager::gameWorld = nullptr;
CWorld_Editable* CWorldManager::editorWorld = nullptr;


/**
 * Loads in a level by slot, automatically unloads the previous level. Can determine whether the level loaded is an editor version or standard.
 * 
 * \param Slot
 * \param bEditorMode
 */
void CWorldManager::LoadWorld(int Slot, bool bEditorMode)
{

	if (bEditorMode)
	{
		//If a game level already exists, unload it first, if switching from game to editor, unload the game.
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
			//Create a new editor world, load and call setup
			editorWorld = new CWorld_Editable();
			editorWorld->LoadWorld(Slot);
			editorWorld->SetupWorld();

		}
	}
	else
	{
		//Works the same as above, only for the game world instead.
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
/**
 * Loads an override object of world, this is primarily used by the game to instantiate child class variants of the existing level class..
 * 
 * \param World
 */

void CWorldManager::LoadWorld(CWorld* World)
{
	if (editorWorld != nullptr)
	{
		editorWorld->UnloadWorld();
	}
	else if (gameWorld != nullptr)
	{
		gameWorld->UnloadWorld();
	}
	else
	{
		gameWorld = World;
		gameWorld->SetupWorld();
	}
}

/**
 * Edit world variant of the load world override.
 * 
 * \param World
 */
void CWorldManager::LoadWorld(CWorld_Editable* World)
{

	if (World != nullptr)
	{
		World->UnloadWorld();
	}
	else if (editorWorld != nullptr)
	{
		editorWorld->UnloadWorld();
	}
	else
	{
		editorWorld = World;
		editorWorld->SetupWorld();
	}
}

